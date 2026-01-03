#include "FileCardRepository.h"
#include "../../domain/entities/cards/DebitCard.h"
#include "../../domain/entities/cards/CreditCard.h"
#include "../../domain/factories/BaseFactory.h"
#include "../utils/FileUtils.h"
#include "../utils/StringUtils.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
namespace filesystem = std::filesystem;

FileCardRepository::FileCardRepository(const string& folderPath)
    : _folder(folderPath) {
    if (!filesystem::exists(_folder)) {
        filesystem::create_directories(_folder);
    }
}

string FileCardRepository::getPath(const string& id) const {
    return _folder + "/" + id + ".txt";
}

shared_ptr<Card> FileCardRepository::loadFromFile(const string& path) {
    auto lines = FileUtils::readLines(path);
    if (lines.empty()) return nullptr;

    string cardType= StringUtils::normalizeString(lines[0]);

    auto card = BaseFactory<Card>::instance().create(cardType, "");
    if (!card) return nullptr;

    lines.erase(lines.begin());

    card->deserialize(lines);
    return card;
}

void FileCardRepository::save(shared_ptr<Card> card) {
    string path = getPath(card->getId());
    FileUtils::writeText(path, card->serialize());
}

bool FileCardRepository::remove(const string& cardId) {
    return filesystem::remove(getPath(cardId));
}

bool FileCardRepository::exists(const string& cardId) {
    return filesystem::exists(getPath(cardId));
}

shared_ptr<Card> FileCardRepository::findByCardId(const string& cardId) {
    string path = getPath(cardId);
    if (!filesystem::exists(path)) return nullptr;
    return loadFromFile(path);
}

vector<shared_ptr<Card>> FileCardRepository::findByUserId(const string& userId) {
    vector<shared_ptr<Card>> res;

    for (auto& f : filesystem::directory_iterator(_folder)) {
        shared_ptr<Card> card = loadFromFile(f.path().string());
        if (card && card->getUserId() == userId)
            res.push_back(card);
    }

    return res;
}

vector<shared_ptr<Card>> FileCardRepository::findByAccountId(const string& accountId) {
    vector<shared_ptr<Card>> res;

    for (auto& f : filesystem::directory_iterator(_folder)) {
        shared_ptr<Card> card = loadFromFile(f.path().string());
        if (card && card->getAccountId() == accountId)
            res.push_back(card);
    }

    return res;
}