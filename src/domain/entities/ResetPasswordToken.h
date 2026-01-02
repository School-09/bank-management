#ifndef _RESET_PASSWORD_TOKEN_H_
#define _RESET_PASSWORD_TOKEN_H_

#include <string>
#include <vector>
using std::string;
using std::vector;

class ResetPasswordToken {
private:
    string _tokenId;
    string _userId;
    string _createdAt;
    string _expiredAt;
    bool _used;

public:
    ResetPasswordToken(string userId);
    ~ResetPasswordToken() = default;

public:
    bool isExpired() const;

    // ======= SERIALIZATION =======
    virtual string serialize() const;
    virtual void deserialize(const vector<string>& lines);

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

};

#endif
