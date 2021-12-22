cmake_minimum_required(VERSION 3.20)

project(SearchServer VERSION 0.0.1)

SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)
FIND_PACKAGE(Boost 1.42.0 REQUIRED COMPONENTS system thread regex)
IF(Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)

SET(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})
set(CMAKE_CXX_STANDARD 17)
include_directories(src)

add_executable(telepong src/main.cpp)
TARGET_LINK_LIBRARIES(telepong ${USED_LIBS})

