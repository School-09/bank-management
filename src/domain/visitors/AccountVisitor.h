#ifndef _ACCOUNT_VISITOR_H_
#define _ACCOUNT_VISITOR_H_

class CheckingAccount;
class CreditAccount;
class SavingAccount;

class AccountVisitor {
public:
    virtual ~AccountVisitor() = default;
    virtual void visit(CheckingAccount& checkingAcc) = 0;
    virtual void visit(CreditAccount& creditAcc) = 0;
    virtual void visit(SavingAccount& savingAcc) = 0;
};

#endif
