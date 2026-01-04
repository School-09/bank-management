#include "IntegerToCurrencyConverter.h"
#include "../../domain/entities/NumberFormatInfo.h"

#include <sstream>
#include <regex>
using std::stringstream;
using std::regex;

string IntegerToCurrencyConverter::convert(int n) {
	stringstream builder;
	NumberFormatInfo info;
	if (n == 0) {
		builder << "0";
	} else {
		int count = 0;

		while (n != 0) {
			int lastDigit = n % 10;
			builder << lastDigit;

			count++;

			if (count == 3 && n >= 10) {
				builder << info.currencyDecimalSeparator();
				count = 0;
			}

			n /= 10;
		}
	}

	string numberSeparated = builder.str(); // "000.000.1"
	reverse(numberSeparated.begin(), numberSeparated.end());
	
	string format = info.currencyPositiveFormat(); // "$n" ==> "$1.000.000"
	string symbol = info.currencySymbol(); // "$"

	string result = regex_replace(format, regex("n"), numberSeparated);
	result = regex_replace(result, regex("\\$"), symbol);

	return result;
}
