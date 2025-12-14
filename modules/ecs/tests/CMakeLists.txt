add_executable(ecs_tests
    ArchetypeComponentsTests.cpp
)

target_link_libraries(ecs_tests
    PRIVATE
        ecs
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(ecs_tests)