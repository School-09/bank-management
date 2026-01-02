#ifndef _FILE_NOTIFICATION_REPOSITORY_H_
#define _FILE_NOTIFICATION_REPOSITORY_H_

#include "../../domain/repositories/INotificationRepository.h"

#include <memory>
using std::shared_ptr, std::make_shared;

class FileNotificationRepository : public INotificationRepository {
private:
    string _folder;
    
private:
    string getPath(const string& id) const;
    shared_ptr<Notification> loadFromFile(const string& path);

public:
    FileNotificationRepository(const string& folder);

public:
    void save(shared_ptr<Notification> nf) override;
    vector<shared_ptr<Notification>> findByUserId(const string& userId) override;

};

#endif