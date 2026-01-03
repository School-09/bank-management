#ifndef _OPTION_ENUM_H_
#define _OPTION_ENUM_H_

enum class AuthMenuOption {
    REGISTER = 1,
    LOGIN = 2,
    RESET_PASSWORD = 3,
    EXIT = 0
};

enum class ResetPasswordMenuOption {
    ENTER_RESET_TOKEN = 1,
    BACK = 0
};

enum class AdminMenuOption {
    ACCOUNT_MANAGE = 1,
    CARD_MANAGE = 2,
    LOGOUT = 3,
    BACK = 0
};

enum class AdminAccountMenuOption {
    CREATE_ACCOUNT = 1,
    OPEN_ACCOUNT = 2,
    CLOSE_ACCOUNT = 3,
    LOGOUT = 4,
    BACK = 0
};

enum class AdminCardMenuOption {
    CREATE_CARD = 1,
    DELETE_CARD = 2,
    BLOCK_CARD = 3,
    UNBLOCK_CARD = 4,
    LOGOUT = 5,
    BACK = 0
};

enum class CustomerMenuOption {
    ACCOUNT_MANAGE = 1,
    TRANSACTION_MANAGE = 2,
    CARD_MANAGE = 3,
    LOGOUT = 4,
    BACK = 0
};

enum class CustomerAccountMenuOption {
    LIST_ACCOUNTS = 1,
    LOGOUT = 2,
    BACK = 0
};

enum class CustomerTransactionMenuOption {
    DEPOSIT = 1,
    WITHDRAW = 2,
    TRANSFER = 3,
    LOGOUT = 4,
    BACK = 0
};

enum class CustomerCardMenuOption {
    LIST_CARDS = 1,
    PAY_WITH_CARD = 2,
    LOGOUT = 3,
    BACK = 0
};

#endif