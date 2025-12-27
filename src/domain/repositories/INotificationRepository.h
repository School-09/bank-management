#ifndef _INOTIFICATIONREPOSITORY_H_
#define _INOTIFICATIONREPOSITORY_H_

#include "../entities/Notification.h"

#include <string>
#include <vector>
#include <memory>
using std::string;
using std::vector;
using std::shared_ptr, std::make_shared;


class INotificationRepository {
public:
    virtual void save(shared_ptr<Notification> nf) = 0;
    virtual vector<shared_ptr<Notification>> findByUserId(const string& userId) = 0;
};

#endif