add_library(ecs STATIC
    src/Commands.cpp
    src/ECS.cpp
    src/World.cpp
)


target_link_libraries(ecs
    PUBLIC
        core
)

target_include_directories(ecs
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(tests)