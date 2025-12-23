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

/* =========================
   APPLICATION
   ========================= */
#include "application/controllers/AuthController.h"
#include "application/controllers/AccountController.h"
#include "application/controllers/MenuController.h"


int main() {
   /* =========================
      PREPARE DATA FOLDERS
      ========================= */
   fs::create_directories(Paths::USERS);
   fs::create_directories(Paths::SESSIONS);
   fs::create_directories(Paths::TOKENS);
   fs::create_directories(Paths::ACCOUNTS);

   /* =========================
      INFRASTRUCTURE
      ========================= */
   auto userRepo    = make_shared<FileUserRepository>(Paths::USERS);
   auto sessionRepo = make_shared<FileSessionRepository>(Paths::SESSIONS);
   auto resetRepo   = make_shared<FileResetPasswordRepository>(Paths::TOKENS);
   auto accountRepo = make_shared<FileAccountRepository>(Paths::ACCOUNTS);

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

   auto menuController = make_shared<MenuController>(
      authController,
      accountController
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
