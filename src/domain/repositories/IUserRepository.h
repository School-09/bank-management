#ifndef I_USER_REPOSITORY_H_
#define I_USER_REPOSITORY_H_

#include "../entities/User.h"

#include <string>
#include <vector>
#include <memory>
using std::string;
using std::vector;
using std::shared_ptr, std::make_shared;

class IUserRepository {
public:
    virtual ~IUserRepository() = default;

public:
    // Create / Update
    virtual void save(shared_ptr<User> user) = 0;

    // Read
    virtual shared_ptr<User> findById(const string& id) = 0;
    virtual shared_ptr<User> findByUsername(const string& username) = 0;
    virtual shared_ptr<User> findByEmail(const string& email) = 0;

    // Delete
    virtual bool remove(const string& id) = 0;

    // Utilities
    virtual bool existsById(const string& id) = 0;
    virtual bool existsByUsername(const string& username) = 0;
    virtual bool existsByEmail(const string& email) = 0;
};

#endif
