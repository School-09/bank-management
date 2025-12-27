#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <string>
using std::string;


class Object {
public:
    virtual ~Object() = default;
    virtual string toString() const = 0;
};

#endif