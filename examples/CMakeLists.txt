SET(PROJECT_TEST ${PROJECT_NAME}-example)

include_directories(${CMAKE_SOURCE_DIR})

set(${PROJECT_TEST}_SOURCES
    example.cpp
)

add_executable(${PROJECT_TEST} ${${PROJECT_TEST}_SOURCES})
target_link_libraries(${PROJECT_TEST} PRIVATE qwtble Qt6::Test Qt6::Widgets)

add_test(NAME ${PROJECT_TEST} COMMAND ${PROJECT_TEST})
