#ifndef _I_ACCOUNT_REPOSITORY_H_
#define _I_ACCOUNT_REPOSITORY_H_

#include "../entities/accounts/Account.h"

#include <memory>
using std::shared_ptr, std::make_shared;

class IAccountRepository {
public:
    virtual ~IAccountRepository() = default;

public:
    virtual void save(shared_ptr<Account> account) = 0;
    virtual bool remove(const string& accountId) = 0;
    virtual bool exists(const string& accountId) = 0;

    virtual shared_ptr<Account> findByAccountId(const string& accountId) = 0;
    virtual vector<shared_ptr<Account>> findByUserId(const string& userId) = 0;
    
};


#endif