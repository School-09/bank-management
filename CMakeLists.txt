cmake_minimum_required(VERSION 3.16)
project(bank_app LANGUAGES CXX)

# Thiết lập chuẩn C++
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Tìm tất cả file .cpp trong src và các thư mục con
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

# Tạo executable từ toàn bộ file .cpp
add_executable(bank_app ${SOURCES})

# Nếu bạn có thư mục include riêng, thêm vào đây
target_include_directories(bank_app PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/include"
)

# Nếu muốn output binary vào thư mục debug/
set_target_properties(bank_app PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
