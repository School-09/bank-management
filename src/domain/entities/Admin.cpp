#include "Admin.h"

string Admin::serialize() const {
    return User::serialize(); // không thêm gì
}

void Admin::deserialize(const vector<string>& lines) {
    User::deserialize(lines);  // không thêm gì
}
