add_executable(basic_ecs
    main.cpp
)

target_link_libraries(basic_ecs
    PRIVATE
        app
        ecs
        log
)