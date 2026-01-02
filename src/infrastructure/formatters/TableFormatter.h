#ifndef TABLEFORMATTER_H
#define TABLEFORMATTER_H

#include "RowFormatter.h"
#include "ColumnFormat.h"
#include <vector>
#include <string>

class TableFormatter {
private:
    vector<RowFormatter> _rows;
    vector<string> _headers;
    vector<ColumnFormat> _colFormats;
    char _colSeparator = '|';
    size_t _padding = 1;
    bool _hasHeader = false;

    vector<size_t> computeColumnWidths() const;

public:
    TableFormatter() = default;

    void setColumnSeparator(char sep) { _colSeparator = sep; }
    void setPadding(size_t pad) { _padding = pad; }
    void setColumnFormats(const vector<ColumnFormat>& formats) { _colFormats = formats; }
    void setHeaders(const vector<string>& headers) { _headers = headers; _hasHeader = true; }

    void addRow(const RowFormatter& row) { _rows.push_back(row); }
    void addRow(vector<string> fields) { _rows.emplace_back(std::move(fields)); }

    vector<string> renderLines() const;
    string render() const;
};

#endif
