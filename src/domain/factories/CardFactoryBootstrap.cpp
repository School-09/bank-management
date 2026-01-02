#include "CardFactoryBootstrap.h"
#include "CardFactory.h"
#include "../entities/DebitCard.h"
#include "../entities/CreditCard.h"

void registerCardTypes() {
    CardFactory::instance().registerType(
        "debitcard",
        []() { return std::make_shared<DebitCard>(); }
    );

    CardFactory::instance().registerType(
        "creditcard",
        []() { return std::make_shared<CreditCard>(); }
    );
}
