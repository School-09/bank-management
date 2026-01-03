#ifndef _DEBIT_CARD_H_
#define _DEBIT_CARD_H_

#include "Card.h"

class DebitCard : public Card {
public:
    DebitCard() = default;
    DebitCard(string userId, string accountId);
    ~DebitCard() override = default;

public: // Visitor Pattern
    void accept(CardVisitor& visitor) override;

public:
    string serialize() const override;
    void deserialize(const vector<string>& lines) override;

};

#endif