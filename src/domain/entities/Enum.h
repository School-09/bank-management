#ifndef _ENUM_H_
#define _ENUM_H_

#include <string>
#include <vector>

// Trạng thái 
enum class Status { 
    ACTIVE, 
    LOCKED 
};

enum class ErrorCode : int {
    // ===== Common (1000–1099) =====
    InvalidInput              = 1000,
    InvalidFormat             = 1001,
    MissingRequiredField      = 1002,

    // ===== Auth (1100–1199) =====
    Unauthorized              = 1100,
    PermissionDenied          = 1101,
    SessionExpired            = 1102,

    // ===== User (1200–1299) =====
    UserNotFound              = 1200,
    UserAlreadyExists         = 1201,
    UserLocked                = 1202,
    EmailNotFound             = 1203,
    EmailAlreadyExists        = 1204,
    InvalidToken              = 1205,
    TokenExpired              = 1206,

    // ===== Account, Card (1300–1399) =====
    AccountNotFound           = 1300,
    AccountAlreadyExists      = 1301,
    AccountClosed             = 1302,
    AccountFrozen             = 1303,
    CardNotFound              = 1304,
    CardLocked                = 1305,
    CardError                 = 1306,

    // ===== Transaction (1400–1499) =====
    InsufficientBalance       = 1400,
    TransactionNotFound       = 1401,
    DuplicateTransaction      = 1402,
    InvalidTransactionAmount  = 1403,

    // ===== Limit / Policy (1500–1599) =====
    AccountLimitExceeded      = 1500,
    DailyTransferLimitExceeded= 1501,
    WithdrawalLimitExceeded  = 1502,
    InvalidPassword         = 1503,

    // ===== Infrastructure mapping (1900–1999) =====
    PersistenceError          = 1900,
    ExternalServiceError      = 1901,
};

#endif