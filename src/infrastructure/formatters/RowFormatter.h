#ifndef _ROW_FORMATTER_H_
#define _ROW_FORMATTER_H_

#include <vector>
#include <string>
using std::string;
using std::vector;
using std::size_t;

class RowFormatter {
private:
    vector<string> _fields;

public:
    RowFormatter() = default;
    explicit RowFormatter(vector<string> fields) 
        : _fields(std::move(fields)) {}

    const vector<string>& fields() const { return _fields; }
    size_t size() const { return _fields.size(); }
};

#endif // ROWFORMATTER_H
