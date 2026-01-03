#ifndef _CREDIT_CARD_H_
#define _CREDIT_CARD_H_

#include "Card.h"

class CreditCard : public Card {
public:
    CreditCard() = default;
    CreditCard(string userId, string accountId);
    ~CreditCard() override = default;

public: // Visitor Pattern
    void accept(CardVisitor& visitor) override;

public:
    string serialize() const override;
    void deserialize(const vector<string>& lines) override;

};

#endif