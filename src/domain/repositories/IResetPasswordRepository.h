#ifndef I_RESET_PASSWORD_REPOSITORY_H_
#define I_RESET_PASSWORD_REPOSITORY_H_

#include "../entities/ResetPasswordToken.h"

#include <string>
#include <vector>
#include <memory>
using std::string;
using std::vector;
using std::shared_ptr, std::make_shared;

class IResetPasswordRepository {
public:
    virtual ~IResetPasswordRepository() = default;

public:
    virtual void save(const ResetPasswordToken& token) = 0;
    virtual bool remove(const string& tokenId) = 0;
    virtual bool exists(const string& tokenId) = 0;

    virtual ResetPasswordToken findByTokenId(const string& tokenId) = 0;
    virtual vector<ResetPasswordToken> findByUserId(const string& userId) = 0;
    
};

#endif