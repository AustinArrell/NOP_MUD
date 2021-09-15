
set(sources
    "main.cpp"
)

add_executable(mud ${sources})

target_include_directories(mud PUBLIC "include")