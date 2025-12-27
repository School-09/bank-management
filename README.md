# bank-management
Bank Management System - C++ OOP

### Chạy với g++
```bash
$ cd src
$ g++ -std=c++23 main.cpp application/*.cpp application/controllers/*.cpp domain/entities/*.cpp domain/factories/*.cpp infrastructure/repositories/*.cpp usecase/auth/*.cpp usecase/account/*.cpp usecase/transaction/*.cpp usecase/card/*.cpp -o debug/app
$ ./debug/app
```

### Chạy với CMake
```bash
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
$ ./../debug/bank_app
```
