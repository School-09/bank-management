#ifndef _FILE_ACCOUNT_REPOSITORY_H_
#define _FILE_ACCOUNT_REPOSITORY_H_

#include "../../domain/repositories/IAccountRepository.h"
#include "../../domain/entities/SavingAccount.h"
#include "../../domain/entities/CheckingAccount.h"
#include "../../domain/entities/CreditAccount.h"
#include "../utils/FileUtils.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <memory>
using std::shared_ptr, std::make_shared;
namespace filesystem = std::filesystem;

class FileAccountRepository : public IAccountRepository {
private:
    string _folder;

private:
    shared_ptr<Account> createAccountByType(const string& type);
    shared_ptr<Account> loadFromFile(const string& path);
    string getPath(const string& id) const;

public:
    FileAccountRepository(const string& folderPath);

public:
    void save(shared_ptr<Account> acc) override;

    shared_ptr<Account> findByAccountId(const string& accountId) override;
    vector<shared_ptr<Account>> findByUserId(const string& userId) override;

    bool remove(const string& accountId) override;

    bool exists(const string& accountId) override;
};

#endif