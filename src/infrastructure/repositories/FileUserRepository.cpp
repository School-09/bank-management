#include "FileUserRepository.h"

shared_ptr<User> FileUserRepository::createUserByType(const string& type) { // TODO factory
    if (type == "Admin") return make_shared<Admin> (Admin());
    if (type == "Customer") return make_shared<Customer> (Customer());
    return nullptr;
}

shared_ptr<User> FileUserRepository::loadFromFile(const string& path) {
    auto lines = FileUtils::readLines(path);
    if (lines.empty()) return nullptr;

    string userType;

    // dòng đầu là UserType: X
    auto pos = lines[7].find(":");
    userType = lines[7].substr(pos + 2);

    shared_ptr<User> user = createUserByType(userType); // TODO factory
    if (!user) return nullptr;

    user->deserialize(lines);
    return user;
}

string FileUserRepository::getPath(const string& id) const {
    return _folder + "/U" + id + ".txt";
}

FileUserRepository::FileUserRepository(const string& folderPath) : _folder(folderPath) {
    filesystem::create_directories(_folder); // TODO check file exist
}

void FileUserRepository::save(shared_ptr<User> user) {
    string path = getPath(user->getId());
    FileUtils::writeText(path, user->serialize());
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
