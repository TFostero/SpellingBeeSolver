add_subdirectory(src)

include_directories(inc)

add_executable(sbsolve 
    src/client.cpp
)