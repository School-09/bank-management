#ifndef _FILECARDREPOSITORY_H_
#define _FILECARDREPOSITORY_H_

#include "../../domain/repositories/ICardRepository.h"
#include "../../domain/entities/DebitCard.h"
#include "../../domain/entities/CreditCard.h"
#include "../utils/FileUtils.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <memory>
using std::shared_ptr, std::make_shared;
namespace filesystem = std::filesystem;

class FileCardRepository : public ICardRepository {
private:
    string _folder;

    shared_ptr<Card> createCardByType(const string& type);
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