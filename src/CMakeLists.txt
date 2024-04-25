include_directories(${PROJECT_SOURCE_DIR}/inc)
add_executable(${PROJECT_SOURCE_DIR}/sbsolve 
    sbsolve.cpp 
    Node.cpp
    Solver.cpp
    Trie.cpp
    ui.cpp)