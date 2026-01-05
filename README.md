# Bank Management System - C++ OOP

Dự án mô phỏng hệ thống quản lý ngân hàng, được xây dựng bằng C++ theo mô hình OOP và Clean Architecture.

---

## 🔧 Yêu cầu hệ thống
- CMake >= 3.15
- Compiler hỗ trợ C++17 hoặc C++20 (g++/clang/MSVC)
- Hệ điều hành: Linux, macOS, hoặc Windows

---

## ⚙️ Hướng dẫn biên dịch

Nếu chưa có thư mục `build`, tạo mới và biên dịch:

```bash

$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ..
$ cmake --build . --config Release
$ ./../Release/bank_app

```

## Một số việc chưa hoàn thành
- edgecase: xử lý dữ nhập vào
- error: xử lý một số lỗi tiềm ẩn
- comment
- sinh tài liệu mô tả
- test chương trình

---------------------------------------------------

- Giúp tôi comment đầy đủ file trên. Yêu cầu: bằng tiếng anh, cấu trúc chuẩn project. Để tôi có thể sinh tài liệu Doxygen.
- Include các header và thư viện đầy đủ (có thể thêm hoặc xóa), đảm bảo không thừa không thiếu, sau đó sắp xếp lại các include 1 cách hợp lý theo thứ tự: header, library, using,.... (những đường dẫn nào bạn ko biết thì cứ ghi tạm, tôi sẽ sửa lại)
- Sử using std:: cho từng loại (để đọc code gọn hơn), ko dùng using namespace std
- Format code, đảm bảo trình bày rõ ràng, chuẩn các quy tắc c++(một dòng ko quá dài, tách dòng, hàm hợp lý, ... và nhiều hơn thế nữa)
- Các câu in ra màn hình hay hơn, đảm bảo tối ưu cho người dùng, ngôn ngữ 100% tiếng việt
