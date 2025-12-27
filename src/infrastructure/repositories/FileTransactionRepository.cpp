#include "FileTransactionRepository.h"
#include "../utils/FileUtils.h"

#include <filesystem>
#include <fstream>
#include <sstream>
namespace filesystem = std::filesystem;


string FileTransactionRepository::getPath(const string& id) const {
    return _folder + "/T" + id + ".txt";
}

shared_ptr<Transaction> FileTransactionRepository::createTransactionByType(const string& type) { // TODO factory
    if (type == "Deposit") return Transaction::createDeposit("", "", 0);
    if (type == "Withdraw") return Transaction::createWithdraw("", "", 0);
    if (type == "Transfer") return Transaction::createTransfer("", "", "", 0);
    return nullptr;
}

shared_ptr<Transaction> FileTransactionRepository::loadFromFile(const string& path) {
    auto lines = FileUtils::readLines(path);
    if (lines.empty()) return nullptr;

    string transactionType;

    // dòng đầu là AccountType: X
    auto pos = lines[5].find(":");
    transactionType = lines[5].substr(pos + 2);
    shared_ptr<Transaction> trans = createTransactionByType(transactionType); // TODO factory
    if (!trans) return nullptr;

    trans->deserialize(lines);
    return trans;
}

FileTransactionRepository::FileTransactionRepository(const string& folderPath) : _folder(folderPath) {
    filesystem::create_directories(_folder); // TODO check file exist
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
