#ifndef _TIMEUTILS_H_
#define _TIMEUTILS_H_

#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>


class TimeUtil {
public:
    static std::string toString(time_t t) {
        std::tm* tm = std::localtime(&t);
        std::ostringstream oss;
        oss << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }
};

#endif