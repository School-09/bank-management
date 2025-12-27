#include "FileAccountRepository.h"
#include "../../domain/factories/AccountFactory.h"

FileAccountRepository::FileAccountRepository(const string& folderPath)
    : _folder(folderPath)
{
    if (!filesystem::exists(_folder)) {
        filesystem::create_directories(_folder);
    }
}

string FileAccountRepository::getPath(const string& id) const {
    return _folder + "/A" + id + ".txt";
}

shared_ptr<Account> FileAccountRepository::loadFromFile(const string& path) {
    auto lines = FileUtils::readLines(path);
    if (lines.empty()) return nullptr;

    string accountType;

    // dòng đầu là AccountType: X
    auto pos = lines[5].find(":");
    if (pos == string::npos) return nullptr;

    accountType = lines[5].substr(pos + 2);

    auto acc = AccountFactory::instance().create(accountType);
    if (!acc) return nullptr;

    acc->deserialize(lines);
    return acc;
}

void FileAccountRepository::save(shared_ptr<Account> acc) {
    string path = getPath(acc->getId());
    FileUtils::writeText(path, acc->serialize());
}

shared_ptr<Account> FileAccountRepository::findByAccountId(const string& accountId) {
    string path = getPath(accountId);
    if (!filesystem::exists(path)) return nullptr;
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

bool FileAccountRepository::exists(const string& accountId) {
    return filesystem::exists(getPath(accountId));
}

bool FileAccountRepository::remove(const string& accountId) {
    return findByAccountId(accountId) != nullptr;
}
