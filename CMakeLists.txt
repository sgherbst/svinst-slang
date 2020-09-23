cmake_minimum_required(VERSION 3.12)
project(svinst-slang VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# turn all warnings on
set(CMAKE_CXX_FLAGS "-Wall -g -Wextra -Werror -fPIC")

# extern
add_subdirectory(extern/slang)

# src
add_subdirectory(src)

#enable_testing()
#add_subdirectory(tests)