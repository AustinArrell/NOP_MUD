### CLIENT ###

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(client_source
    "${CMAKE_SOURCE_DIR}/common/network.cpp"
    "./main.cpp"
    "./client.cpp"
    "./input_field.cpp"
    "./state_manager.cpp"
    "./game_state.cpp"
    "./login_state.cpp"
    "./output_field.cpp"
    "./text_field.cpp"
    "./button.cpp"
)

add_executable(mudclient ${client_source})

target_include_directories(mudclient PUBLIC "${CMAKE_SOURCE_DIR}/common")
target_link_libraries(mudclient sfml-system sfml-window sfml-graphics sfml-network)
