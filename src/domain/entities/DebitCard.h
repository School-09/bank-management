#ifndef _DEBITCARD_H_
#define _DEBITCARD_H_

#include "Card.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <map>
#include <functional>
using std::vector;
using std::string;

class DebitCard : public Card {
public:
    string getType() const override { return "Debit"; }
    string getLinkedAccountId() const override { return _accountId; }

    string serialize() const override;
    void deserialize(const vector<string>& lines) override;
};

#endif