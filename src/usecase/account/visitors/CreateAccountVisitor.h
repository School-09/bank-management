#ifndef _CREATE_ACCOUNT_VISITOR_H_
#define _CREATE_ACCOUNT_VISITOR_H_

#include "../../../domain/entities/Account.h"
#include "../../../domain/visitors/AccountVisitor.h"
#include <string>
#include <vector>
#include <memory>
using std::string;
using std::vector;
using std::shared_ptr, std::make_shared;

class CreateAccountVisitor : public AccountVisitor {
public:
    void visit(CheckingAccount& checkingAcc) override;
    void visit(CreditAccount& creditAcc) override;
    void visit(SavingAccount& savingAcc) override;
};

#endif
