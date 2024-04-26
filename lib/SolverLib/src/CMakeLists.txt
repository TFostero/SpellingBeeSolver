include_directories(${PROJECT_SOURCE_DIR}/lib/SolverLib/inc)

add_library(SolverLib 
    Node.cpp
    Solver.cpp
    Trie.cpp
)