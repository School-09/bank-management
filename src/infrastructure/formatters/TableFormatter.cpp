#include "TableFormatter.h"

#include <algorithm>
#include <format>
#include <sstream>
using std::format;
using std::max;
using std::ostringstream;

vector<size_t> TableFormatter::computeColumnWidths() const {
    size_t cols = 0;
    if (_hasHeader) cols = max(cols, _headers.size());
    for (const auto& r : _rows) cols = max(cols, r.size());

    vector<size_t> widths(cols, 0);

    if (_hasHeader) {
        for (size_t i = 0; i < _headers.size(); ++i) {
            widths[i] = max(widths[i], _headers[i].size());
        }
    }

    for (const auto& r : _rows) {
        const auto& f = r.fields();
        for (size_t i = 0; i < f.size(); ++i) {
            widths[i] = max(widths[i], f[i].size());
        }
    }

    for (size_t i = 0; i < widths.size(); ++i) {
        if (i < _colFormats.size()) {
            const auto& cf = _colFormats[i];
            if (cf.minWidth > widths[i]) widths[i] = cf.minWidth;
            if (cf.maxWidth > 0 && widths[i] > cf.maxWidth) widths[i] = cf.maxWidth;
        }
    }

    return widths;
}

vector<string> TableFormatter::renderLines() const {
    vector<string> lines;
    auto widths = computeColumnWidths();
    size_t cols = widths.size();

    auto buildLine = [&](const vector<string>& cells) {
        std::ostringstream oss;
        oss << _colSeparator;
        for (size_t i = 0; i < cols; ++i) {
            string cell = (i < cells.size() ? cells[i] : "");
            Alignment align = Alignment::Left;
            if (i < _colFormats.size()) align = _colFormats[i].alignment;
            size_t w = widths[i];

            string formatted;
            switch (align) {
                case Alignment::Left:
                    formatted = format("{:<{}}", cell, w);
                    break;
                case Alignment::Right:
                    formatted = format("{:>{}}", cell, w);
                    break;
                case Alignment::Center:
                    formatted = format("{:^{}}", cell, w);
                    break;
            }

            oss << string(_padding, ' ') << formatted << string(_padding, ' ') << _colSeparator;
        }
        return oss.str();
    };

    if (_hasHeader) {
        // tô vàng cho header 
        auto headerLine = buildLine(_headers);
        lines.push_back("\033[33m" + headerLine + "\033[0m"); // Mã màu vàng (foreground yellow): "\033[33m"

        std::ostringstream sep;
        sep << _colSeparator;
        for (size_t i = 0; i < cols; ++i) {
            size_t total = widths[i] + 2 * _padding;
            sep << string(total, '-') << _colSeparator;
        }
        lines.push_back(sep.str());
    }

    for (const auto& r : _rows) {
        lines.push_back(buildLine(r.fields()));
    }

    return lines;
}

string TableFormatter::render() const {
    auto lines = renderLines();
    ostringstream oss;
    for (size_t i = 0; i < lines.size(); ++i) {
        oss << lines[i];
        if (i + 1 < lines.size()) oss << '\n';
    }
    return oss.str();
}

