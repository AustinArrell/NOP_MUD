### CLIENT ###

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(client_source
    "./main.cpp"
    "./input_field.cpp"
    "./state_manager.cpp"
    "./game_state.cpp"
    "./output_field.cpp"
    "./text_field.cpp"
)

add_executable(mudclient ${client_source})

target_link_libraries(mudclient sfml-main sfml-system sfml-window sfml-graphics sfml-network)