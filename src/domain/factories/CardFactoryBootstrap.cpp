#include "CardFactoryBootstrap.h"
#include "CardFactory.h"
#include "../entities/DebitCard.h"
#include "../entities/CreditCard.h"

void registerCardTypes() {
    CardFactory::instance().registerType(
        "DebitCard",
        []() { return std::make_shared<DebitCard>(); }
    );

    CardFactory::instance().registerType(
        "CreditCard",
        []() { return std::make_shared<CreditCard>(); }
    );
}
