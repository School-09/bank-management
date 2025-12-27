#include "FileCardRepository.h"
#include "../../domain/entities/DebitCard.h"
#include "../../domain/entities/CreditCard.h"
#include "../../domain/factories/CardFactory.h"
#include "../utils/FileUtils.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
namespace filesystem = std::filesystem;


FileCardRepository::FileCardRepository(const string& folderPath)
    : _folder(folderPath)
{
    if (!filesystem::exists(_folder)) {
        filesystem::create_directories(_folder);
    }
}

string FileCardRepository::getPath(const string& id) const {
    return _folder + "/C" + id + ".txt";
}

shared_ptr<Card> FileCardRepository::loadFromFile(const string& path) {
    auto lines = FileUtils::readLines(path);
    if (lines.empty()) return nullptr;

    string cardType;

    // dòng đầu là AccountType: X
    auto pos = lines[7].find(":");
    if (pos == string::npos) return nullptr;

    cardType = lines[7].substr(pos + 2);

    auto card = CardFactory::instance().create(cardType);
    if (!card) return nullptr;

    card->deserialize(lines);
    return card;
}

void FileCardRepository::save(shared_ptr<Card> card) {
    string path = getPath(card->getId());
    FileUtils::writeText(path, card->serialize());
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

bool FileCardRepository::exists(const string& cardId) {
    return filesystem::exists(getPath(cardId));
}

bool FileCardRepository::remove(const string& cardId) {
    return findByCardId(cardId) != nullptr;
}
