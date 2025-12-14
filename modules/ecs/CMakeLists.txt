add_library(ecs STATIC
    src/Commands.cpp
    src/ECS.cpp
    src/World.cpp
)

target_include_directories(ecs
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)