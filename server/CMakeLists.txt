### CLIENT ###

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(server_source
    "./main.cpp"
)

add_executable(mudserver ${server_source})

target_link_libraries(mudserver sfml-main sfml-system sfml-network)