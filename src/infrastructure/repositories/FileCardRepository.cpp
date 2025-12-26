#include "FileCardRepository.h"

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

shared_ptr<Card> FileCardRepository::createCardByType(const string& type) {
    if (type == "DEBIT") return make_shared<DebitCard> (DebitCard());
    if (type == "CREDIT") return make_shared<CreditCard>(CreditCard());
    throw std::runtime_error("Unknown card type: " + type);
}

shared_ptr<Card> FileCardRepository::loadFromFile(const string& path) {
    auto lines = FileUtils::readLines(path);
    if (lines.empty()) return nullptr;

    string cardType;

    // dòng đầu là AccountType: X
    auto pos = lines[7].find(":");
    cardType = lines[7].substr(pos + 2);
    shared_ptr<Card> card = createCardByType(cardType); // TODO factory
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
