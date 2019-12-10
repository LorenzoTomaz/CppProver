cmake_minimum_required(VERSION 2.6)
project(prover)
include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(prover ${SOURCES})

set_property(TARGET prover PROPERTY CXX_STANDARD 17)
target_link_libraries(prover)
# TODO: Run -Werror in CI.
target_compile_options(prover  PRIVATE -std=c++17 -Wall -Wextra -g)
