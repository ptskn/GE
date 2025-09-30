set(projectName "G2E")

cmake_minimum_required(VERSION 3.31)
project(${projectName} VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 26)
#set(CMAKE_CXX_COMPILER_CLANG_SCAN_DEPS "/usr/bin/clang-scan-deps-18")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread -g")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-tree-slp-vectorize")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIE")
add_definitions(-w)

find_package(PostgreSQL REQUIRED)
#find_package(mysql-concpp REQUIRED)
include_directories(${PostgreSQL_INCLUDE_DIRS})
link_directories(${PostgreSQL_LIB_DIRS})
add_definitions(${PostgreSQL_FLAGS})

find_package(OpenSSL REQUIRED)
include_directories(${OpenSSL_INCLUDE_DIRS})
link_directories(${OPENSSL_LIBRARIES})
#/usr/local/lib
string(CONCAT MosquittoLibPath "/home/ptskn/Bureau/code/Libs/mosquitto/build/lib")
string(CONCAT MosquittoSrcPath "/home/ptskn/Bureau/code/Libs/mosquitto/include")
#find_package(PkgConfig REQUIRED)
#pkg_check_modules(Mosquitto IMPORTED_TARGET mosquitto REQUIRED)
include_directories(${MosquittoSrcPath})
link_directories(${MosquittoLibPath})
#add_definitions(${MosquittoSrcPath})

add_executable(${projectName}
        src/Main.cpp
)

target_sources(${projectName}
        PRIVATE

        src/TimeManagementService/MessageDispatcher.cpp
        src/TimeManagementService/MosquittoAsyncClient.cpp
        src/TimeManagementService/ScheduledTask.cpp
        src/TimeManagementService/TransactionManager.cpp

)

target_compile_definitions(${projectName}
        PRIVATE
)

target_link_libraries(${projectName}

        PRIVATE

        PUBLIC
        ${MosquittoLibPath}/libmosquitto.so
)
