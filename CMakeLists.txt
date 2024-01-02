cmake_minimum_required(VERSION 3.9)
project(qr_control)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -static-libgcc -static-libstdc++")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DCURL_STATICLIB")

include_directories(libjpeg)

add_executable(qr_control main.cpp main.h Request.cpp Request.h Response.cpp Response.h Config.cpp Config.h)
find_library (CURL_LIB libcurl PATHS ${qr_control_SOURCE_DIR}/lib)
find_library (QUIRC_LIB libquirc PATHS ${qr_control_SOURCE_DIR}/lib)
TARGET_LINK_LIBRARIES(qr_control ${CURL_LIB} ${QUIRC_LIB})
