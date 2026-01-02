#ifndef _FILE_SESSION_REPOSITORY_H_
#define _FILE_SESSION_REPOSITORY_H_

#include "../../domain/repositories/ISessionRepository.h"

class FileSessionRepository : public ISessionRepository {
private:
    string _folder;

private:
    string getPath(const string& id) const;

public:
    FileSessionRepository(const string& folderPath);

public:
    void save(const Session& session) override;
    bool remove(const string& sessionId) override;
    bool exists(const string& sessionId) override;

    Session findBySessionId(const string& sessionId) override;
    vector<Session> findByUserId(const string& userId) override;

    Session getActiveSession() override;
    void clearActiveSession() override;
};

#endif