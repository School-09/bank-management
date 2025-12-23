#ifndef I_RESET_PASSWORD_REPOSITORY_H_
#define I_RESET_PASSWORD_REPOSITORY_H_

#include "../entities/ResetPasswordToken.h"
#include <string>
#include <vector>
#include <memory>
using std::shared_ptr, std::make_shared;

using std::string;
using std::vector;

class IResetPasswordRepository {
public:
    virtual ~IResetPasswordRepository() = default;

public:
    // Create / Update
    virtual void save(const ResetPasswordToken& token) = 0;

    // Read
    virtual ResetPasswordToken findById(const string& tokenId) = 0;
    virtual vector<ResetPasswordToken> findByUserId(const string& userId) = 0;

    // Delete
    virtual bool remove(const string& tokenId) = 0;

    // Utilities
    virtual bool exists(const string& tokenId) = 0;
};

#endif