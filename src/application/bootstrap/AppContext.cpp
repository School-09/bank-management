#include "AppContext.h"
#include <filesystem>
#include <memory>

#include "../config/Paths.h"

// repositories
#include "../../infrastructure/repositories/FileUserRepository.h"
#include "../../infrastructure/repositories/FileSessionRepository.h"
#include "../../infrastructure/repositories/FileResetPasswordRepository.h"
#include "../../infrastructure/repositories/FileAccountRepository.h"
#include "../../infrastructure/repositories/FileTransactionRepository.h"
#include "../../infrastructure/repositories/FileNotificationRepository.h"
#include "../../infrastructure/repositories/FileCardRepository.h"

// use cases
#include "../../usecase/auth/RegisterUseCase.h"
#include "../../usecase/auth/LoginUseCase.h"
#include "../../usecase/auth/LogoutUseCase.h"
#include "../../usecase/auth/ResetPasswordUseCase.h"

#include "../../usecase/account/GetAccountUseCase.h"
#include "../../usecase/account/CreateAccountUseCase.h"
#include "../../usecase/account/CloseAccountUseCase.h"

#include "../../usecase/transaction/DepositUseCase.h"
#include "../../usecase/transaction/WithdrawUseCase.h"
#include "../../usecase/transaction/TransferUseCase.h"

#include "../../usecase/card/CreateCardUseCase.h"
#include "../../usecase/card/ListCardUseCase.h"
#include "../../usecase/card/DeleteCardUseCase.h"
#include "../../usecase/card/BlockCardUseCase.h"
#include "../../usecase/card/CardPaymentUseCase.h"

// controllers
#include "../controllers/AuthController.h"
#include "../controllers/AccountController.h"
#include "../controllers/TransactionController.h"
#include "../controllers/CardController.h"
#include "../controllers/MenuController.h"

using std::make_shared;
using std::shared_ptr;

std::shared_ptr<MenuController> AppContext::build() {
    namespace fs = std::filesystem;

    // prepare folders
    fs::create_directories(Paths::USERS);
    fs::create_directories(Paths::SESSIONS);
    fs::create_directories(Paths::TOKENS);
    fs::create_directories(Paths::ACCOUNTS);
    fs::create_directories(Paths::TRANSACTIONS);
    fs::create_directories(Paths::NOTIFICATIONS);
    fs::create_directories(Paths::CARDS);

    // repositories
    auto userRepo = make_shared<FileUserRepository>(Paths::USERS);
    auto sessionRepo = make_shared<FileSessionRepository>(Paths::SESSIONS);
    auto resetRepo = make_shared<FileResetPasswordRepository>(Paths::TOKENS);
    auto accountRepo = make_shared<FileAccountRepository>(Paths::ACCOUNTS);
    auto transactionRepo = make_shared<FileTransactionRepository>(Paths::TRANSACTIONS);
    auto notificationRepo = make_shared<FileNotificationRepository>(Paths::NOTIFICATIONS);
    auto cardRepo = make_shared<FileCardRepository>(Paths::CARDS);

    // use cases
    auto registerUC = make_shared<RegisterUseCase>(userRepo);
    auto loginUC = make_shared<LoginUseCase>(userRepo, sessionRepo);
    auto logoutUC = make_shared<LogoutUseCase>(sessionRepo);
    auto resetUC = make_shared<ResetPasswordUseCase>(userRepo, resetRepo);

    auto getAccUC = make_shared<GetAccountUseCase>(accountRepo);
    auto createAccUC = make_shared<CreateAccountUseCase>(accountRepo);
    auto closeAccUC = make_shared<CloseAccountUseCase>(accountRepo, cardRepo);

    auto depositUC = make_shared<DepositUseCase>(accountRepo, transactionRepo, notificationRepo);
    auto withdrawUC = make_shared<WithdrawUseCase>(accountRepo, transactionRepo, notificationRepo);
    auto transferUC = make_shared<TransferUseCase>(accountRepo, transactionRepo, notificationRepo);

    auto createCardUC = make_shared<CreateCardUseCase>(cardRepo, accountRepo);
    auto listCardUC = make_shared<ListCardUseCase>(cardRepo);
    auto deleteCardUC = make_shared<DeleteCardUseCase>(cardRepo, accountRepo);
    auto blockCardUC = make_shared<BlockCardUseCase>(cardRepo, accountRepo);
    auto payCardUC = make_shared<CardPaymentUseCase>(
        cardRepo, accountRepo, transactionRepo, notificationRepo
    );

    // controllers
    auto authController = make_shared<AuthController>(
        registerUC, loginUC, logoutUC, resetUC
    );
    auto accountController = make_shared<AccountController>(
        getAccUC, createAccUC, closeAccUC, sessionRepo
    );
    auto transactionController = make_shared<TransactionController>(
        depositUC, withdrawUC, transferUC, sessionRepo
    );
    auto cardController = make_shared<CardController>(
        createCardUC, listCardUC, deleteCardUC, blockCardUC, payCardUC, sessionRepo
    );

    return make_shared<MenuController>(
        authController,
        accountController,
        transactionController,
        cardController
    );
}
