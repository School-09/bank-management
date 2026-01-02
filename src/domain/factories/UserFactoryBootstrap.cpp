#include "UserFactoryBootstrap.h"
#include "UserFactory.h"
#include "../entities/Admin.h"
#include "../entities/Customer.h"

void registerUserTypes() {
    UserFactory::instance().registerType(
        "admin",
        []() { return std::make_shared<Admin>(); }
    );

    UserFactory::instance().registerType(
        "customer",
        []() { return std::make_shared<Customer>(); }
    );
}
