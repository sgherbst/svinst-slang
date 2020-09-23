cmake_minimum_required(VERSION 3.12)
project(svinst-slang VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# turn all warnings on
set(CMAKE_CXX_FLAGS "-Wall -g -Wextra -Werror -fPIC")

# slang
add_subdirectory(extern/slang)

# main target
add_executable(svinst-slang src/svinst-slang.cpp)
target_link_libraries(svinst-slang PRIVATE slangcompiler)
if(STATIC_BUILD)
    target_link_libraries(svinst-slang PRIVATE -static -Wl,--whole-archive -lpthread -Wl,--no-whole-archive)
endif()
target_include_directories(svinst-slang PUBLIC extern/cxxopts/include)