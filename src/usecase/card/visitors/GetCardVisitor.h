#ifndef _GET_CARD_VISITOR_H_
#define _GET_CARD_VISITOR_H_

#include "../../../domain/visitors/CardVisitor.h"
#include <string>
#include <vector>
#include <format>
using std::string;
using std::vector;
using std::format;

class GetCardVisitor : public CardVisitor {
private:
    vector<vector<string>> _results;

public:
    void visit(DebitCard& debitCard) override;
    void visit(CreditCard& creditCard) override;

    const vector<vector<string>> getResults() const { 
        return _results;
    }
};

#endif
