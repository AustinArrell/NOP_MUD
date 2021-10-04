### CLIENT ###

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(server_source
    "${CMAKE_SOURCE_DIR}/common/network.cpp"
    "./main.cpp"
    "./server.cpp"
)

add_executable(mudserver ${server_source})

target_include_directories(mudserver PUBLIC "${CMAKE_SOURCE_DIR}/common")
target_link_libraries(mudserver sfml-system sfml-network)