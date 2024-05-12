add_subdirectory(src)

include_directories(inc)

add_executable(client 
    src/client.cpp
)