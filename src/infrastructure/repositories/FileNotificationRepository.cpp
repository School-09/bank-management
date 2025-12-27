#include "FileNotificationRepository.h"
#include "../utils/FileUtils.h"

#include <filesystem>
#include <fstream>
#include <sstream>
namespace filesystem = std::filesystem;


string FileNotificationRepository::getPath(const string& id) const {
    return _folder + "/N" + id + ".txt";
}

shared_ptr<Notification> FileNotificationRepository::loadFromFile(const string& path) {
    auto lines = FileUtils::readLines(path);
    if (lines.empty()) return nullptr;

    shared_ptr<Notification> trans;
    trans->deserialize(lines);

    return trans;
}

FileNotificationRepository::FileNotificationRepository(const string& folderPath) : _folder(folderPath) {
    filesystem::create_directories(_folder); // TODO check file exist
}

void FileNotificationRepository::save(shared_ptr<Notification> nf) {
    string path = getPath(nf->getId());
    FileUtils::writeText(path, nf->serialize());
}

vector<shared_ptr<Notification>> FileNotificationRepository::findByUserId(const string& userId) {
     vector<shared_ptr<Notification>> res;

    for (auto& f : filesystem::directory_iterator(_folder)) {
        shared_ptr<Notification> notif = loadFromFile(f.path().string());
        if (notif && notif->getUserId() == userId)
            res.push_back(notif);
    }

    return res;
}
