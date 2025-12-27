#include "UserFactoryBootstrap.h"
#include "UserFactory.h"
#include "../entities/Admin.h"
#include "../entities/Customer.h"

void registerUserTypes() {
    UserFactory::instance().registerType(
        "Admin",
        []() { return std::make_shared<Admin>(); }
    );

    UserFactory::instance().registerType(
        "Customer",
        []() { return std::make_shared<Customer>(); }
    );
}
