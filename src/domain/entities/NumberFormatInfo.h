#ifndef _NUMBER_FORMAT_INFO_H_
#define _NUMBER_FORMAT_INFO_H_

#include <string>
using std::string;

class NumberFormatInfo {
private:
	string _currencyDecimalSeparator = ".";
	string _currencySymbol = "d";

	int _currencyPositive = 3;				// 0		1		2		3
	string _currencyPositiveFormat = "n d"; // "$n"		"n$"	"$ n"	"n $"

public:
	string currencyDecimalSeparator();
	string currencySymbol();
	int currencyPositive();
	string currencyPositiveFormat();

};

#endif