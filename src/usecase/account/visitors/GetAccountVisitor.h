#ifndef _GET_ACCOUNT_VISITOR_H_
#define _GET_ACCOUNT_VISITOR_H_

#include "../../../domain/visitors/AccountVisitor.h"
#include <string>
#include <vector>
#include <format>
using std::string;
using std::vector;
using std::format;

class GetAccountVisitor : public AccountVisitor {
private:
    vector<vector<string>> _results;

public:
    void visit(CheckingAccount& checkingAcc) override;
    void visit(CreditAccount& creditAcc) override;
    void visit(SavingAccount& savingAcc) override;

    const vector<vector<string>> getResults() const { 
        return _results;
    }
};

#endif
