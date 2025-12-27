#ifndef _DEBITCARD_H_
#define _DEBITCARD_H_

#include "Card.h"

#include <iostream>
#include <string>
#include <vector>
using std::vector;
using std::string;


class DebitCard : public Card {
public:
    ~DebitCard() override = default;

    string getType() const override { return "DebitCard"; }
    string getLinkedAccountId() const override { return _accountId; }

    string serialize() const override;
    void deserialize(const vector<string>& lines) override;

    string toString() const override { return "Debit Card"; };
};

#endif