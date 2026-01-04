#include "ErrorMapper.h"

string ErrorMapper::errorMessage(ErrorCode code) {
    switch (code) {
        // ===== Common (1000–1099) =====
        case ErrorCode::InvalidInput:
            return "Dữ liệu đầu vào không hợp lệ";
        case ErrorCode::InvalidFormat:
            return "Định dạng không hợp lệ";
        case ErrorCode::MissingRequiredField:
            return "Thiếu trường bắt buộc";

        // ===== Auth (1100–1199) =====
        case ErrorCode::Unauthorized:
            return "Chưa được xác thực";
        case ErrorCode::PermissionDenied:
            return "Không có quyền truy cập";
        case ErrorCode::SessionExpired:
            return "Phiên làm việc đã hết hạn";

        // ===== User (1200–1299) =====
        case ErrorCode::UserNotFound:
            return "Không tìm thấy người dùng";
        case ErrorCode::UserAlreadyExists:
            return "Người dùng đã tồn tại";
        case ErrorCode::UserLocked:
            return "Tài khoản người dùng đã bị khóa";
        case ErrorCode::EmailNotFound:
            return "Không tìm thấy email";
        case ErrorCode::EmailAlreadyExists:
            return "Email đã tồn tại";
        case ErrorCode::InvalidToken:
            return "Token không hợp lệ";
        case ErrorCode::TokenExpired:
            return "Token đã hết hạn";

        // ===== Account (1300–1399) =====
        case ErrorCode::AccountNotFound:
            return "Không tìm thấy tài khoản";
        case ErrorCode::AccountAlreadyExists:
            return "Tài khoản đã tồn tại";
        case ErrorCode::AccountClosed:
            return "Tài khoản đã đóng";
        case ErrorCode::AccountFrozen:
            return "Tài khoản đã bị phong tỏa";
        case ErrorCode::CardNotFound:
            return "Không tìm thấy thẻ";
        case ErrorCode::CardLocked:
            return "Thẻ đã bị khóa";
        case ErrorCode::CardError:
            return "Thẻ lỗi";

        // ===== Transaction (1400–1499) =====
        case ErrorCode::InsufficientBalance:
            return "Số dư không đủ để thực hiện giao dịch";
        case ErrorCode::TransactionNotFound:
            return "Không tìm thấy giao dịch";
        case ErrorCode::DuplicateTransaction:
            return "Giao dịch bị trùng lặp";
        case ErrorCode::InvalidTransactionAmount:
            return "Số tiền giao dịch không hợp lệ";

        // ===== Limit / Policy (1500–1599) =====
        case ErrorCode::AccountLimitExceeded:
            return "Đã vượt quá số lượng tài khoản cho phép";
        case ErrorCode::DailyTransferLimitExceeded:
            return "Đã vượt quá hạn mức chuyển khoản trong ngày";
        case ErrorCode::WithdrawalLimitExceeded:
            return "Đã vượt quá hạn mức rút tiền";
        case ErrorCode::InvalidPassword:
            return "Mật khẩu không đúng";

        // ===== Infrastructure mapping (1900–1999) =====
        case ErrorCode::PersistenceError:
            return "Lỗi hệ thống lưu trữ dữ liệu";
        case ErrorCode::ExternalServiceError:
            return "Lỗi từ dịch vụ bên ngoài";

        default:
            return "Lỗi hệ thống không xác định";
    }
}
