#include "AccountFactoryBootstrap.h"
#include "AccountFactory.h"
#include "../entities/CheckingAccount.h"
#include "../entities/SavingAccount.h"
#include "../entities/CreditAccount.h"

void registerAccountTypes() {
    AccountFactory::instance().registerType(
        "CheckingAccount",
        []() { return std::make_shared<CheckingAccount>(); }
    );

    AccountFactory::instance().registerType(
        "SavingAccount",
        []() { return std::make_shared<SavingAccount>(); }
    );

    AccountFactory::instance().registerType(
        "CreditAccount",
        []() { return std::make_shared<CreditAccount>(); }
    );
}
