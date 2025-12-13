add_library(app STATIC
    src/App.cpp
)

target_link_libraries(app
    PRIVATE
        ecs
)

target_include_directories(app
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)