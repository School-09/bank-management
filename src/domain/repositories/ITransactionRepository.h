#ifndef _ITRANSACTIONREPOSITORY_H_
#define _ITRANSACTIONREPOSITORY_H_

#include "../entities/Transaction.h"

#include <string>
#include <vector>
#include <memory>
using std::string;
using std::vector;
using std::shared_ptr, std::make_shared;

class ITransactionRepository {
public:
    virtual ~ITransactionRepository() = default;

public:
    virtual void save(shared_ptr<Transaction> tx) = 0;
    virtual vector<shared_ptr<Transaction>> findByUserId(const string& userId) = 0;
};

#endif