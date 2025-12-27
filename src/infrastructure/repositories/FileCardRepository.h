#ifndef _FILECARDREPOSITORY_H_
#define _FILECARDREPOSITORY_H_

#include "../../domain/repositories/ICardRepository.h"

#include <memory>
using std::shared_ptr, std::make_shared;


class FileCardRepository : public ICardRepository {
private:
    string _folder;

private:
    shared_ptr<Card> loadFromFile(const string& path);
    string getPath(const string& id) const;

public:
    FileCardRepository(const string& folder);

    void save(shared_ptr<Card> card) override;
    vector<shared_ptr<Card>> findByUserId(const string& userId) override;
    shared_ptr<Card> findByCardId(const string& cardId) override;
    bool exists(const string& cardId) override;
    bool remove(const string& id) override;
};

#endif