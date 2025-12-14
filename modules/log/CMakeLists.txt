add_library(log STATIC
    src/Logger.cpp
    src/Log.cpp
    src/LogLevel.cpp
)

target_include_directories(log
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)