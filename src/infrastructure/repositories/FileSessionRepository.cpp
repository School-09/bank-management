#include "FileSessionRepository.h"
#include "../utils/FileUtils.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <stdexcept>
namespace filesystem = std::filesystem;


string FileSessionRepository::getPath(const string& id) const {
    return _folder + "/S" + id + ".txt";
}

FileSessionRepository::FileSessionRepository(const string& folderPath) : _folder(folderPath) {
    filesystem::create_directories(_folder);
}

void FileSessionRepository::save(const Session& session) {
    FileUtils::writeText(getPath(session.getSessionId()), session.serialize());
}

Session FileSessionRepository::findById(const string& sessionId) {
    string path = getPath(sessionId);
    Session s;
    if (filesystem::exists(path)) {
        auto lines = FileUtils::readLines(path);
        s.deserialize(lines);
    }
    return s;
}

vector<Session> FileSessionRepository::findByUserId(const string& userId) {
    vector<Session> result;

    for (auto& f : filesystem::directory_iterator(_folder)) {
        Session s;
        auto lines = FileUtils::readLines(f.path().string());
        s.deserialize(lines);

        if (s.getUserId() == userId) result.push_back(s);
    }
    return result;
}

bool FileSessionRepository::remove(const string& sessionId) {
    return filesystem::remove(getPath(sessionId));
}

bool FileSessionRepository::exists(const string& sessionId) {
    return filesystem::exists(getPath(sessionId));
}

Session FileSessionRepository::getActiveSession() {
    for (auto& f : filesystem::directory_iterator(_folder)) {
        vector<string> lines = FileUtils::readLines(f.path().string());

        Session s;
        s.deserialize(lines);

        if (!s.isExpired()) {
            return s;
        }
    }

    throw std::runtime_error("No active session found");
}


void FileSessionRepository::clearActiveSession() {
    for (auto& entry : filesystem::directory_iterator(_folder)) {
        filesystem::remove(entry.path());
    }
}
