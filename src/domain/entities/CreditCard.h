#ifndef _CREDITCARD_H_
#define _CREDITCARD_H_

#include "Card.h"

#include <iostream>
#include <string>
#include <vector>
using std::vector;
using std::string;


class CreditCard : public Card {
public:
    ~CreditCard() override = default;

    string getType() const override { return "CreditCard"; }
    string getLinkedAccountId() const override { return _accountId; }

    string serialize() const override;
    void deserialize(const vector<string>& lines) override;

    string toString() const override { return "Credit Card"; };
};

#endif