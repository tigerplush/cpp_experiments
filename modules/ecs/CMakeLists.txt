add_library(ecs STATIC
    src/Commands.cpp
    src/ECS.cpp
    src/World.cpp
)

add_executable(ecs_tests
    tests/ArchetypeComponentsTests.cpp
    tests/WorldTests.cpp
)

target_link_libraries(ecs_tests
    PRIVATE
        ecs
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(ecs_tests)


target_link_libraries(ecs
    PUBLIC
        core
        log
)

target_include_directories(ecs
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
