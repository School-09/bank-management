# bank-management
Bank Management System - C++ OOP

### Chạy với g++
```bash
$ cd src
$ g++ -std=c++23 main.cpp 
application/ui/*.cpp application/controllers/*.cpp application/menu/*.cpp 
domain/entities/*.cpp domain/factories/*.cpp 
infrastructure/repositories/*.cpp infrastructure/converters/*.cpp infrastructure/formatters/*.cpp infrastructure/utils/*.cpp 
usecase/auth/*.cpp usecase/account/*.cpp usecase/account/visitors/*.cpp usecase/transaction/*.cpp usecase/card/*.cpp usecase/card/visitors/*.cpp -o debug/app
$ ./debug/app
```

### Chạy với g++ ngắn
```bash
$ g++ -std=c++23 $(find src -name "*.cpp") -o debug/app
```

### Chạy với CMake
```bash
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .

$ cd build
$ ./../Debug/bank_app
```

