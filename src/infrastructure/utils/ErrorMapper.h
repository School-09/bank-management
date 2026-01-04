#ifndef _ERROR_MAPPER_H_
#define _ERROR_MAPPER_H_

#include "../../domain/entities/Enum.h"

#include <string>
using std::string;

class ErrorMapper {
public:
	static string errorMessage(ErrorCode code);
};

#endif