#ifndef _FILE_CARD_REPOSITORY_H_
#define _FILE_CARD_REPOSITORY_H_

#include "../../domain/repositories/ICardRepository.h"

#include <memory>
using std::shared_ptr, std::make_shared;

class FileCardRepository : public ICardRepository {
private:
    string _folder;

private:
    string getPath(const string& id) const;
    shared_ptr<Card> loadFromFile(const string& path);

public:
    FileCardRepository(const string& folder);

public:
    void save(shared_ptr<Card> card) override;
    bool remove(const string& id) override;
    bool exists(const string& cardId) override;
    
    shared_ptr<Card> findByCardId(const string& cardId) override;
    vector<shared_ptr<Card>> findByUserId(const string& userId) override;
    vector<shared_ptr<Card>> findByAccountId(const string& accountId) override;

};

#endif