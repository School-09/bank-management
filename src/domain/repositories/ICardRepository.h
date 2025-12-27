#ifndef _ICARDREPOSITORY_H_
#define _ICARDREPOSITORY_H_

#include "../entities/Card.h"

#include <memory>
using std::shared_ptr, std::make_shared;


class ICardRepository {
public:
    virtual ~ICardRepository() = default;

public:
    virtual void save(shared_ptr<Card> card) = 0;
    virtual vector<shared_ptr<Card>> findByUserId(const string& userId) = 0;
    virtual shared_ptr<Card> findByCardId(const string& id) = 0;
    virtual bool remove(const string& id) = 0;
    virtual bool exists(const string& cardId) = 0;
};

#endif