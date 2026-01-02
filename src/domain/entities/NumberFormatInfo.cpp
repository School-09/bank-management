#include "NumberFormatInfo.h"

string NumberFormatInfo::currencyDecimalSeparator() {
    return this->_currencyDecimalSeparator;
}

string NumberFormatInfo::currencySymbol() {
    return this->_currencySymbol;
}

int NumberFormatInfo::currencyPositive() {
    return this->_currencyPositive;
}

string NumberFormatInfo::currencyPositiveFormat() {
    return this->_currencyPositiveFormat;
}
