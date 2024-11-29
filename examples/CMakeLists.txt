SET(PROJECT_TEST ${PROJECT_NAME}-example)

include_directories($<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)

set(${PROJECT_TEST}_SOURCES
    example.cpp
)

add_executable(${PROJECT_TEST} ${${PROJECT_TEST}_SOURCES})
target_link_libraries(${PROJECT_TEST} PRIVATE qwtble Qt6::Test Qt6::Widgets)
