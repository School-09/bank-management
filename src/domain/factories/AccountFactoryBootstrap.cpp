#include "AccountFactoryBootstrap.h"
#include "AccountFactory.h"
#include "../entities/CheckingAccount.h"
#include "../entities/SavingAccount.h"
#include "../entities/CreditAccount.h"

void registerAccountTypes() {
    AccountFactory::instance().registerType(
        "checkingaccount",
        []() { return std::make_shared<CheckingAccount>(); }
    );

    AccountFactory::instance().registerType(
        "savingaccount",
        []() { return std::make_shared<SavingAccount>(); }
    );

    AccountFactory::instance().registerType(
        "creditaccount",
        []() { return std::make_shared<CreditAccount>(); }
    );
}
