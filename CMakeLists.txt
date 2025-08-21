cmake_minimum_required(VERSION 3.10)

# اسم پروژه
project(neo_hookean_plugin LANGUAGES CXX)

# تنظیمات C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# سورس فایل‌ها
set(SOURCES
    dllmain.cpp
    FENeoHookeanPI.cpp
)

set(HEADERS
    FENeoHookeanPI.h
)

# ساخت کتابخانه داینامیک (DLL یا .so)
add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
