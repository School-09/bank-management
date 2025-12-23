#ifndef SESSION_H
#define SESSION_H

#include "../../infrastructure/utils/FileUtils.h"

#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <functional>
using std::string;
using std::vector;

class Session {
private:
    string _sessionId;
    string _userId;
    string _createdAt;
    string _expiredAt;

public:
    Session() = default;

    Session(const string& sessionId,
            const string& userId,
            const string& createdAt,
            const string& expiredAt)
        : _sessionId(sessionId),
          _userId(userId),
          _createdAt(createdAt),
          _expiredAt(expiredAt) {}

    virtual ~Session() = default;

public:
    // ========= GETTER =========
    string getSessionId() const { return _sessionId; }
    string getUserId() const { return _userId; }
    string getCreatedAt() const { return _createdAt; }
    string getExpiredAt() const { return _expiredAt; }

    // ========= SETTER =========
    void setSessionId(const string& sessionId) { _sessionId = sessionId; }
    void setUserId(const string& userId) { _userId = userId; }
    void setCreatedAt(const string& createdAt) { _createdAt = createdAt; }
    void setExpiredAt(const string& expiredAt) { _expiredAt = expiredAt; }

public:
    // ========= FILE SERIALIZATION  =========
    virtual string serialize() const;
    virtual void deserialize(const vector<string>& lines);

    bool isExpired() const;
};

#endif
