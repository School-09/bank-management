#ifndef _FILEUSERREPOSITORY_H_
#define _FILEUSERREPOSITORY_H_

#include "../../domain/repositories/IUserRepository.h"

#include <memory>
using std::shared_ptr, std::make_shared;


class FileUserRepository : public IUserRepository {
private:
    string _folder;

private:
    shared_ptr<User> loadFromFile(const string& path);
    string getPath(const string& id) const;

public:
    FileUserRepository(const string& folderPath);

public:
    void save(shared_ptr<User> user) override;

    shared_ptr<User> findById(const string& id) override;
    shared_ptr<User> findByUsername(const string& username) override;
    shared_ptr<User> findByEmail(const string& email) override;

    bool remove(const string& id) override;

    bool existsById(const string& id) override;
    bool existsByUsername(const string& username) override;
    bool existsByEmail(const string& email) override;
 
};

#endif