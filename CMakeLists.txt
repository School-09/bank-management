cmake_minimum_required(VERSION 3.16)

# Tên project
project(BankManagementConsole LANGUAGES CXX)

# Chuẩn C++
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Thư mục chứa source
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

# Gom tất cả file cpp
file(GLOB_RECURSE SOURCES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/application/*.cpp
    ${SRC_DIR}/application/controllers/*.cpp
    ${SRC_DIR}/domain/entities/*.cpp
    ${SRC_DIR}/infrastructure/repositories/*.cpp
    ${SRC_DIR}/usecase/auth/*.cpp
    ${SRC_DIR}/usecase/account/*.cpp
    ${SRC_DIR}/usecase/transaction/*.cpp
    ${SRC_DIR}/usecase/card/*.cpp
)

# Tạo executable
add_executable(bank_app ${SOURCES})

# Output binary vào thư mục debug/
set_target_properties(bank_app PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/debug
)
