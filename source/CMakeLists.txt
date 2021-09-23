
set(sources
    "main.cpp"
    "input_field.cpp"
    "state_manager.cpp"
    "game_state.cpp"
    "output_field.cpp"
    "text_field.cpp"
)

add_executable(mud ${sources})

target_include_directories(mud PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(mud -L sfml/lib -lsfml-graphics -lsfml-window -lsfml-system)