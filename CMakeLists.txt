cmake_minimum_required(VERSION 3.14)

project(SpellingBeeSolver)
add_subdirectory(lib)
# add_subdirectory(test)

enable_testing()

include_directories(${PROJECT_SOURCE_DIR}/inc)

add_executable(sbsolve 
    src/sbsolve.cpp 
    src/ui.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/lib/SolverLib/inc)
target_link_libraries(sbsolve PUBLIC SolverLib)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
  sbsolve_test
  test/sbsolve_test.cc
)

target_link_libraries(sbsolve_test PUBLIC
  SolverLib
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(sbsolve_test)
