#include <iostream>
#include <filesystem>
#include <memory>
using std::cin, std::cout;
using std::shared_ptr, std::make_shared;
namespace fs = std::filesystem;

#include "application/config/Paths.h"

/* =========================
   REPOSITORIES (INFRA)
   ========================= */
#include "infrastructure/repositories/FileUserRepository.h"
#include "infrastructure/repositories/FileSessionRepository.h"
#include "infrastructure/repositories/FileResetPasswordRepository.h"
#include "infrastructure/repositories/FileAccountRepository.h"
#include "infrastructure/repositories/FileTransactionRepository.h"
#include "infrastructure/repositories/FileNotificationRepository.h"
#include "infrastructure/repositories/FileCardRepository.h"

/* =========================
   USE CASES
   ========================= */
#include "usecase/auth/RegisterUseCase.h"
#include "usecase/auth/LoginUseCase.h"
#include "usecase/auth/LogoutUseCase.h"
#include "usecase/auth/ResetPasswordUseCase.h"
#include "usecase/account/GetAccountUseCase.h"
#include "usecase/account/CreateAccountUseCase.h"
#include "usecase/account/CloseAccountUseCase.h"
#include "usecase/transaction/DepositUseCase.h"
#include "usecase/transaction/WithdrawUseCase.h"
#include "usecase/transaction/TransferUseCase.h"
#include "usecase/card/CreateCardUseCase.h"
#include "usecase/card/ListCardUseCase.h"
#include "usecase/card/DeleteCardUseCase.h"
#include "usecase/card/BlockCardUseCase.h"
#include "usecase/card/CardPaymentUseCase.h"

/* =========================
   APPLICATION
   ========================= */
#include "application/controllers/MenuController.h"   
#include "application/controllers/AuthController.h"
#include "application/controllers/AccountController.h"
#include "application/controllers/TransactionController.h"
#include "application/controllers/CardController.h"


int main() {
   /* =========================
      PREPARE DATA FOLDERS
      ========================= */
   fs::create_directories(Paths::USERS);
   fs::create_directories(Paths::SESSIONS);
   fs::create_directories(Paths::TOKENS);
   fs::create_directories(Paths::ACCOUNTS);
   fs::create_directories(Paths::TRANSACTIONS);
   fs::create_directories(Paths::NOTIFICATIONS);
   fs::create_directories(Paths::CARDS);

   /* =========================
      INFRASTRUCTURE
      ========================= */
   auto userRepo    = make_shared<FileUserRepository>(Paths::USERS);
   auto sessionRepo = make_shared<FileSessionRepository>(Paths::SESSIONS);
   auto resetRepo   = make_shared<FileResetPasswordRepository>(Paths::TOKENS);
   auto accountRepo = make_shared<FileAccountRepository>(Paths::ACCOUNTS);
   auto transactionRepo = make_shared<FileTransactionRepository>(Paths::TRANSACTIONS);
   auto notificationRepo = make_shared<FileNotificationRepository>(Paths::NOTIFICATIONS);
   auto cardRepo    = make_shared<FileCardRepository>(Paths::CARDS);

   /* =========================
      USE CASES
      ========================= */
   auto registerUseCase   = make_shared<RegisterUseCase>(userRepo);
   auto loginUseCase      = make_shared<LoginUseCase>(userRepo, sessionRepo);
   auto logoutUseCase     = make_shared<LogoutUseCase>(sessionRepo);
   auto resetUseCase      = make_shared<ResetPasswordUseCase>(userRepo, resetRepo);

   auto getAccountsUseCase   = make_shared<GetAccountUseCase>(accountRepo);
   auto createAccountUseCase = make_shared<CreateAccountUseCase>(accountRepo);
   auto closeAccountUseCase  = make_shared<CloseAccountUseCase>(accountRepo);

   auto depositUseCase  = make_shared<DepositUseCase>(accountRepo, transactionRepo, notificationRepo);
   auto withdrawUseCase  = make_shared<WithdrawUseCase>(accountRepo, transactionRepo, notificationRepo);
   auto transferUseCase  = make_shared<TransferUseCase>(accountRepo, transactionRepo, notificationRepo);

   auto createCardUseCase = make_shared<CreateCardUseCase>(cardRepo, accountRepo);
   auto listCardUseCase   = make_shared<ListCardUseCase>(cardRepo);
   auto deleteCardUseCase = make_shared<DeleteCardUseCase>(cardRepo, accountRepo);
   auto blockCardUseCase  = make_shared<BlockCardUseCase>(cardRepo, accountRepo);
   auto cardPaymentUseCase = make_shared<CardPaymentUseCase>(cardRepo, accountRepo, transactionRepo); // add notificatonRepo

   /* =========================
      CONTROLLER
      ========================= */
      
   auto authController = make_shared<AuthController>(
      registerUseCase,
      loginUseCase,
      logoutUseCase,
      resetUseCase
   );
   auto accountController = make_shared<AccountController>(
      getAccountsUseCase,
      createAccountUseCase,
      closeAccountUseCase,
      sessionRepo
   );
   auto transactionController = make_shared<TransactionController>(
      depositUseCase,
      withdrawUseCase,
      transferUseCase,
      sessionRepo
   );
   auto cardController = make_shared<CardController>(
      createCardUseCase,
      listCardUseCase,
      deleteCardUseCase,
      blockCardUseCase,
      cardPaymentUseCase,
      sessionRepo
   );
   auto menuController = make_shared<MenuController>(
      authController,
      accountController,
      transactionController,
      cardController
   );

   /* =========================
      RUN TEST
      ========================= */
   menuController->runAuthMenu();

   cout << "\nProgram is exiting. Please type ENTER to exit...";
   cin.get();

   cout << "\n=== EXIT PROGRAM ===\n";

   return 0;
}
