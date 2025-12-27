#ifndef I_SESSION_REPOSITORY_H_
#define I_SESSION_REPOSITORY_H_

#include "../entities/Session.h"

#include <string>
#include <vector>
#include <memory>
using std::string;
using std::vector;
using std::shared_ptr, std::make_shared;


class ISessionRepository {
public:
    virtual ~ISessionRepository() = default;

public:
    // Create/Update
    virtual void save(const Session& session) = 0;

    // Read
    virtual Session findById(const string& sessionId) = 0;
    virtual vector<Session> findByUserId(const string& userId) = 0;

    // Delete
    virtual bool remove(const string& sessionId) = 0;

    // Utilities
    virtual bool exists(const string& sessionId) = 0;

    virtual Session getActiveSession() = 0;

    virtual void clearActiveSession() = 0;
};

#endif
