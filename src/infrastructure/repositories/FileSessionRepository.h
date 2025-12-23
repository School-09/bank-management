#ifndef _FILESESSIONREPOSITORY_H_
#define _FILESESSIONREPOSITORY_H_

#include "../../domain/repositories/ISessionRepository.h"
#include "../../domain/entities/Session.h"
#include "../utils/FileUtils.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <stdexcept>
namespace filesystem = std::filesystem;

class FileSessionRepository : public ISessionRepository {
private:
    string _folder;
    string getPath(const string& id) const;

public:
    FileSessionRepository(const string& folderPath);

public:
    void save(const Session& session) override;

    Session findById(const string& sessionId) override;
    vector<Session> findByUserId(const string& userId) override;

    bool remove(const string& sessionId) override;
    
    bool exists(const string& sessionId) override;

    Session getActiveSession() override;
    void clearActiveSession() override;
};

#endif