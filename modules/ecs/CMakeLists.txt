add_library(ecs STATIC
    src/ECS.cpp
)

target_include_directories(ecs
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)