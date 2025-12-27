#ifndef _NOTIFICATION_H_
#define _NOTIFICATION_H_

#include "Object.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>
using std::string;
using std::vector;
using std::shared_ptr, std::make_shared;


class Notification : public Object{
private:
    string _id;
    string _userId;
    string _message;
    string _createdAt;
    bool _read;

public:
    static shared_ptr<Notification> create(
        const string& userId,
        const string& message
    );

public:
    string getId() const { return _id; }
    string getUserId() const { return _userId; }

public:
    string serialize() const;
    void deserialize(const vector<string>& lines);

    string toString() const override { return "Notification"; };
};

#endif