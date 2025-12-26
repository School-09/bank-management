#ifndef _ENUM_H_
#define _ENUM_H_

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

// Trạng thái chung
enum class Status { 
    ACTIVE, 
    LOCKED 
};

// Vai trò người dùng
enum class Role { 
    CUSTOMER, 
    ADMIN 
};

enum class AccountType {
    SAVING,
    CHECKING,
    CREDIT
};


// Loại giao dịch
enum class TransactionType { 
    DEPOSIT, 
    WITHDRAW, 
    TRANSFER 
};

enum class CardType { 
    DEBIT,
    CREDIT
};

// Loại tiền tệ (nếu cần)
enum class Currency { 
    VND, 
    USD 
};

#endif