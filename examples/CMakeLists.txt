SET(PROJECT_EXAMPLES ${PROJECT_NAME}-examples)

set(${PROJECT_EXAMPLES}_SOURCES
    example.cpp
)

add_executable(${PROJECT_EXAMPLES} ${${PROJECT_EXAMPLES}_SOURCES})
target_link_libraries(${PROJECT_EXAMPLES} PRIVATE qwtble Qt6::Test Qt6::Widgets)

if (WIN32)
    add_custom_command(TARGET ${PROJECT_EXAMPLES} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_BINARY_DIR}/../qwt/install/lib" "$<TARGET_FILE_DIR:${PROJECT_EXAMPLES}>")
endif()
