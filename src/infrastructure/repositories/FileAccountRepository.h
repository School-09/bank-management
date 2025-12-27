#ifndef _FILE_ACCOUNT_REPOSITORY_H_
#define _FILE_ACCOUNT_REPOSITORY_H_

#include "../../domain/repositories/IAccountRepository.h"

#include <memory>
using std::shared_ptr, std::make_shared;


class FileAccountRepository : public IAccountRepository {
private:
    string _folder;

private:
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