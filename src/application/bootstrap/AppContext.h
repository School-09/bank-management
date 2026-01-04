#ifndef _APP_CONTEXT_H_
#define _APP_CONTEXT_H_

#include <memory>

#include "../controllers/MenuController.h";

class AppContext {
public:
    static std::shared_ptr<MenuController> build();
};

#endif
