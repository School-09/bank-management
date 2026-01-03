#include "LogoutUseCase.h"

bool LogoutUseCase::execute(const string& sessionId) {
    if (!_sessionRepo->exists(sessionId))
        return false;

    return _sessionRepo->remove(sessionId);
}