set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(sources
    "main.cpp"
    "input_field.cpp"
    "state_manager.cpp"
    "game_state.cpp"
    "output_field.cpp"
    "text_field.cpp"
    "nouns.cpp"
    "verbs.cpp"
    "parser.cpp"
    "room.cpp"
    "mobile.cpp"
    
)

add_executable(mud ${sources})

target_include_directories(mud PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(mud -L sfml/lib -lsfml-graphics -lsfml-window -lsfml-system)