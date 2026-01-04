#include "FileTransactionRepository.h"
#include "../../domain/factories/BaseFactory.h"
#include "../utils/FileUtils.h"
#include "../utils/StringUtils.h"

#include <filesystem>
#include <fstream>
#include <sstream>
namespace filesystem = std::filesystem;

FileTransactionRepository::FileTransactionRepository(const string& folderPath) 
    : _folder(folderPath) {
    if (!filesystem::exists(_folder)) {
        filesystem::create_directories(_folder);
    }
}

string FileTransactionRepository::getPath(const string& id) const {
    return _folder +  "/" + id + ".txt";
}

shared_ptr<Transaction> FileTransactionRepository::loadFromFile(const string& path) {
    auto lines = FileUtils::readLines(path);
    if (lines.empty()) return nullptr;

    string transactionType = StringUtils::normalizeString(lines[0]);

    auto trans = BaseFactory<Transaction>::instance().create(transactionType, "");
    if (!trans) return nullptr;

    lines.erase(lines.begin());

    trans->deserialize(lines);
    return trans;
}

void FileTransactionRepository::save(shared_ptr<Transaction> tx) {
    string path = getPath(tx->getId());
    FileUtils::writeText(path, tx->serialize());
}

vector<shared_ptr<Transaction>> FileTransactionRepository::findByUserId(const string& userId) {
     vector<shared_ptr<Transaction>> res;

    for (auto& f : filesystem::directory_iterator(_folder)) {
        shared_ptr<Transaction> trans = loadFromFile(f.path().string());
        if (trans && trans->getUserId() == userId)
            res.push_back(trans);
    }

    return res;
}
