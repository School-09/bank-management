#ifndef _CARD_H_
#define _CARD_H_

#include "../Enum.h"
#include "../../visitors/CardVisitor.h"

#include <iostream>
#include <string>
#include <vector>
using std::vector;
using std::string;

class Card {
protected:
    string _id;
    string _userId;
    string _accountId;
    string _cardNumber;
    string _createdAt;
    string _expiredAt;
    Status _status;

public:
    Card() = default;
    Card(string id, string userId, string accountId);
    virtual ~Card() = default;

public: // Visitor Pattern
    virtual void accept(CardVisitor& visitor) = 0;

public:
    // ===== PERSISTENCE =====
    virtual string serialize() const = 0;
    virtual void deserialize(const vector<string>& lines) = 0;

public:
    string getId() const { return _id; }
    string getUserId() const { return _userId; }
    string getAccountId() const { return _accountId; }
    string getCardNumber() const { return _cardNumber; }
    string getCreatedAt() const { return _createdAt; }
    string getExpiredAt() const { return _expiredAt; }

    void setId(string id) { _id = id; }
    void setUserId(string userId) { _userId = userId; }
    void setAccountId(string accountId) { _accountId = accountId; }
    void setCardNumber(string cardNumber) { _cardNumber = cardNumber; }

    bool isLocked() const { return _status == Status::LOCKED; }
    void lock() { _status = Status::LOCKED; }
    void unlock() { _status = Status::ACTIVE; }

};

#endif
