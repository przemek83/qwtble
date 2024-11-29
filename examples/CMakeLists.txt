SET(PROJECT_EXAMPLES ${PROJECT_NAME}-examples)

set(${PROJECT_EXAMPLES}_SOURCES
    example.cpp
)

add_executable(${PROJECT_EXAMPLES} ${${PROJECT_EXAMPLES}_SOURCES})
target_link_libraries(${PROJECT_EXAMPLES} PRIVATE qwtble Qt6::Test Qt6::Widgets)
