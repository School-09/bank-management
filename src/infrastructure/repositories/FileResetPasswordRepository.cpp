#include "FileResetPasswordRepository.h"
#include "../utils/FileUtils.h"

#include <filesystem>
namespace filesystem = std::filesystem;

FileResetPasswordRepository::FileResetPasswordRepository(const string& folderPath) 
    : _folder(folderPath) {
    if (!filesystem::exists(_folder)) {
        filesystem::create_directories(_folder);
    }
}

string FileResetPasswordRepository::getPath(const string& id) const {
    return _folder + "/P" + id + ".txt";
}

void FileResetPasswordRepository::save(const ResetPasswordToken& token) {
    FileUtils::writeText(getPath(token.getTokenId()), token.serialize());
}

bool FileResetPasswordRepository::remove(const string& tokenId) {
    return filesystem::remove(getPath(tokenId));
}

bool FileResetPasswordRepository::exists(const string& tokenId) {
    return filesystem::exists(getPath(tokenId));
}

ResetPasswordToken FileResetPasswordRepository::findByTokenId(const string& tokenId) {
    ResetPasswordToken t;
    string path = getPath(tokenId);

    if (filesystem::exists(path)) {
        auto lines = FileUtils::readLines(path);
        t.deserialize(lines);
    }
    return t;
}

vector<ResetPasswordToken> FileResetPasswordRepository::findByUserId(const string& userId) {
    vector<ResetPasswordToken> result;

    for (auto& f : filesystem::directory_iterator(_folder)) {
        ResetPasswordToken t;
        auto lines = FileUtils::readLines(f.path().string());
        t.deserialize(lines);

        if (t.getUserId() == userId) result.push_back(t);
    }
    return result;
}
