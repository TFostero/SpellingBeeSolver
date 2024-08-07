cmake_minimum_required(VERSION 3.14)

project(SpellingBeeSolver)
add_subdirectory(lib)
add_subdirectory(client)

enable_testing()

include_directories(${PROJECT_SOURCE_DIR}/inc)

add_executable(sbsolved 
    src/sbsolve.cpp 
)

set(CMAKE_CXX_FLAGS -pthread)

include_directories(${PROJECT_SOURCE_DIR}/lib/SolverLib/inc)
target_link_libraries(sbsolved PUBLIC SolverLib)

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
  trie_test
  test/trie_test.cc
)

target_link_libraries(trie_test PUBLIC
  SolverLib
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(trie_test)

add_subdirectory(packaging)
install(TARGETS sbsolved sbsolve
        DESTINATION /usr/bin
)