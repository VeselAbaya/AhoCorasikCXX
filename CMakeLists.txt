cmake_minimum_required(VERSION 3.10)
project(AhoCorasik)

set(CMAKE_CXX_STANDARD 14)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# dirs
include_directories(header src test)

add_executable(AhoCorasik src/main.cpp header/AhoCorasik.h src/AhoCorasik.cpp)
add_executable(AhoCorasik2 src/main2.cpp header/AhoCorasik2.h src/AhoCorasik2.cpp src/main2.cpp)

# test
add_executable(AhoCorasik_test header/AhoCorasik.h src/AhoCorasik.cpp test/AhoCorasik_test.cpp)
target_link_libraries(AhoCorasik_test ${GTEST_LIBRARIES} pthread)

add_executable(AhoCorasik2_test header/AhoCorasik2.h src/AhoCorasik2.cpp test/AhoCorasik2_test.cpp)
target_link_libraries(AhoCorasik2_test ${GTEST_LIBRARIES} pthread)