#ifndef _FILE_USER_REPOSITORY_H_
#define _FILE_USER_REPOSITORY_H_

#include "../../domain/repositories/IUserRepository.h"

#include <memory>
using std::shared_ptr, std::make_shared;

class FileUserRepository : public IUserRepository {
private:
    string _folder;

private:
    string getPath(const string& id) const;
    shared_ptr<User> loadFromFile(const string& path);

public:
    FileUserRepository(const string& folderPath);

public:
    void save(shared_ptr<User> user) override;
    bool remove(const string& id) override;
    bool existsById(const string& id) override;
    bool existsByUsername(const string& username) override;
    bool existsByEmail(const string& email) override;

    shared_ptr<User> findById(const string& id) override;
    shared_ptr<User> findByUsername(const string& username) override;
    shared_ptr<User> findByEmail(const string& email) override;
};

#endif