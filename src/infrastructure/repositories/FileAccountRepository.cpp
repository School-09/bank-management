#include "FileAccountRepository.h"
#include "../../domain/factories/BaseFactory.h"
#include "../utils/FileUtils.h"
#include "../utils/StringUtils.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
namespace filesystem = std::filesystem;

FileAccountRepository::FileAccountRepository(const string& folderPath)
    : _folder(folderPath) {
    if (!filesystem::exists(_folder)) {
        filesystem::create_directories(_folder);
    }
}

string FileAccountRepository::getPath(const string& id) const {
    return _folder + "/" + id + ".txt";
}

shared_ptr<Account> FileAccountRepository::loadFromFile(const string& path) {
    auto lines = FileUtils::readLines(path);
    
    if (lines.empty()) return nullptr;

    string accountType = StringUtils::normalizeString(lines[0]);

    auto acc = BaseFactory<Account>::instance().create(accountType, "");
    if (!acc) {
        return nullptr;
    }

    lines.erase(lines.begin());
 
    acc->deserialize(lines);
    return acc;
}

void FileAccountRepository::save(shared_ptr<Account> account) {
    string path = getPath(account->getId());
    FileUtils::writeText(path, account->serialize());
}

bool FileAccountRepository::remove(const string& accountId) {
    return filesystem::remove(getPath(accountId));
}

bool FileAccountRepository::exists(const string& accountId) {
    return filesystem::exists(getPath(accountId));
}

shared_ptr<Account> FileAccountRepository::findByAccountId(const string& accountId) {
    string path = getPath(accountId);
    if (!filesystem::exists(path)) {
        std::cout << "Ko thay file " << path << "\n";
        return nullptr;
    }
    return loadFromFile(path);
}

vector<shared_ptr<Account>> FileAccountRepository::findByUserId(const string& userId) {
    vector<shared_ptr<Account>> res;

    for (auto& f : filesystem::directory_iterator(_folder)) {
        shared_ptr<Account> acc = loadFromFile(f.path().string());

        if (acc && acc->getUserId() == userId)
            res.push_back(acc);
    }

    return res;
}
