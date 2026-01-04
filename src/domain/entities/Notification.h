#ifndef _NOTIFICATION_H_
#define _NOTIFICATION_H_

#include <string>
#include <vector>
using std::string;
using std::vector;

class Notification {
private:
    string _id;
    string _userId;
    string _message;
    string _createdAt;
    bool _read;

public:
    Notification() = default;
    Notification(string userId, string message);
    ~Notification() = default;

public:
    string serialize() const;
    void deserialize(const vector<string>& lines);
    
public:
    string getId() const { return _id; }
    string getUserId() const { return _userId; }

};

#endif