#include "TransactionFactoryBootstrap.h"
#include "TransactionFactory.h"
#include "../entities/Deposit.h"
#include "../entities/Withdraw.h"
#include "../entities/Transfer.h"

void registerTransactionTypes() {
    TransactionFactory::instance().registerType(
        "deposit",
        []() { return std::make_shared<Deposit>(); }
    );

    TransactionFactory::instance().registerType(
        "withdraw",
        []() { return std::make_shared<Withdraw>(); }
    );

    TransactionFactory::instance().registerType(
        "transfer",
        []() { return std::make_shared<Transfer>(); }
    );
}
