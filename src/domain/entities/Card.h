#ifndef _CARD_H_
#define _CARD_H_

#include "Object.h"

#include <iostream>
#include <string>
#include <vector>
using std::vector;
using std::string;


class Card : public Object{
protected:
    string _id;
    string _userId;
    string _accountId;
    string _cardNumber;
    string _expiredAt;
    string _cvv;
    bool _blocked;

public:
    Card();
    virtual ~Card() = default;

    void setUserId(string userId) { _userId = userId; }
    void setAccountId(string accountId) { _accountId = accountId; }

    // ===== POLYMORPHISM =====
    virtual string getType() const = 0;
    virtual string getLinkedAccountId() const = 0;

    bool isBlocked() const { return _blocked; }
    void block() { _blocked = true; }
    void unblock() { _blocked = false; }

    string getUserId() const { return _userId; }
    string getId() const { return _id; }

    // ===== PERSISTENCE =====
    virtual string serialize() const = 0;
    virtual void deserialize(const vector<string>& lines) = 0;

    virtual string toString() const override { return "Card"; };
};

#endif
