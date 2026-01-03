#include "FileUserRepository.h"
#include "../../domain/factories/BaseFactory.h"
#include "../utils/FileUtils.h"
#include "../utils/StringUtils.h"

#include <filesystem>
#include <fstream>
#include <sstream>
namespace filesystem = std::filesystem;

FileUserRepository::FileUserRepository(const string& folderPath) 
    : _folder(folderPath) {
    if (!filesystem::exists(_folder)) {
        filesystem::create_directories(_folder);
    }
}

string FileUserRepository::getPath(const string& id) const {
    return _folder +  "/" + id + ".txt";
}

shared_ptr<User> FileUserRepository::loadFromFile(const string& path) {
    auto lines = FileUtils::readLines(path);
    if (lines.empty()) return nullptr;

    string userType = StringUtils::normalizeString(lines[0]);

    auto user = BaseFactory<User>::instance().create(userType, "");
    if (!user) return nullptr;

    lines.erase(lines.begin());

    user->deserialize(lines);
    return user;
}

void FileUserRepository::save(shared_ptr<User> user) {
    string path = getPath(user->getId());
    FileUtils::writeText(path, user->serialize());
}

bool FileUserRepository::remove(const string& id) {
    return filesystem::remove(getPath(id));
}

bool FileUserRepository::existsById(const string& id) {
    return filesystem::exists(getPath(id));
}

bool FileUserRepository::existsByUsername(const string& username) {
    return findByUsername(username) != nullptr;
}

bool FileUserRepository::existsByEmail(const string& email) {
    return findByEmail(email) != nullptr;
}

shared_ptr<User> FileUserRepository::findById(const string& id) {
    string path = getPath(id);
    if (!filesystem::exists(path)) return nullptr;
    return loadFromFile(path);
}

shared_ptr<User> FileUserRepository::findByUsername(const string& username) {
    for (auto& f : filesystem::directory_iterator(_folder)) {
        shared_ptr<User> user = loadFromFile(f.path().string());
        if (user && user->getUsername() == username)
            return user;
    }
    return nullptr;
}

shared_ptr<User> FileUserRepository::findByEmail(const string& email) {
    for (auto& f : filesystem::directory_iterator(_folder)) {
        shared_ptr<User> user = loadFromFile(f.path().string());
        if (user && user->getEmail() == email)
            return user;
    }
    return nullptr;
}
