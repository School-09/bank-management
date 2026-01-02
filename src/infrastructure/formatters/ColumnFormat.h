#ifndef _COLUMN_FORMAT_H_
#define _COLUMN_FORMAT_H_

#include <cstddef>
using std::size_t;

enum class Alignment {
    Left,
    Right,
    Center
};

class ColumnFormat {
public:
    Alignment alignment = Alignment::Left;
    size_t minWidth = 0;
    size_t maxWidth = 0; // 0 = no limit
    ColumnFormat() = default;
    ColumnFormat(Alignment a, size_t minW, size_t maxW = 0)
        : alignment(a), minWidth(minW), maxWidth(maxW) {}
    
};

#endif // _COLUMN_FORMAT_H_
