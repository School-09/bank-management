#ifndef RESET_PASSWORD_TOKEN_H
#define RESET_PASSWORD_TOKEN_H

#include "Object.h"

#include <string>
#include <vector>
using std::string;
using std::vector;


class ResetPasswordToken : public Object{
private:
    string _tokenId;
    string _userId;
    string _createdAt;
    string _expiredAt;
    bool _used;

public:
    ResetPasswordToken() = default;

    ResetPasswordToken(const string& tokenId,
                       const string& userId,
                       const string& createdAt,
                       const string& expiredAt,
                       bool used)
        : _tokenId(tokenId),
          _userId(userId),
          _createdAt(createdAt),
          _expiredAt(expiredAt),
          _used(used)
    {}

    virtual ~ResetPasswordToken() = default;

public:
    // ======= GETTER =======
    string getTokenId() const { return _tokenId; }
    string getUserId() const { return _userId; }
    string getCreatedAt() const { return _createdAt; }
    string getExpiredAt() const { return _expiredAt; }
    bool getUsed() const { return _used; }

    // ======= SETTER =======
    void setTokenId(const string& tokenId) { _tokenId = tokenId; }
    void setUserId(const string& userId) { _userId = userId; }
    void setCreatedAt(const string& createdAt) { _createdAt = createdAt; }
    void setExpiredAt(const string& expiredAt) { _expiredAt = expiredAt; }

public:
    // ======= SERIALIZATION =======
    virtual string serialize() const;
    virtual void deserialize(const vector<string>& lines);

    string toString() const override { return "Reset Password Token"; };

    bool isExpired() const;
};

#endif
