SET(PROJECT_TEST ${PROJECT_NAME}-tests)

set(${PROJECT_TEST}_SOURCES
    Tests.cpp
    UtilitiesTest.h
    UtilitiesTest.cpp
    GroupPlotUITest.h
    GroupPlotUITest.cpp
    QuantilesTest.h
    QuantilesTest.cpp
)

add_executable(${PROJECT_TEST} ${${PROJECT_TEST}_SOURCES})
target_link_libraries(${PROJECT_TEST} PRIVATE qwtble Qt6::Test Qt6::Widgets)

if (WIN32)
    add_custom_command(TARGET ${PROJECT_TEST} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_BINARY_DIR}/../qwt/install/lib" "$<TARGET_FILE_DIR:${PROJECT_TEST}>")
endif()

add_test(NAME ${PROJECT_TEST} COMMAND ${PROJECT_TEST})
set_property(TEST ${PROJECT_TESTS} PROPERTY FAIL_REGULAR_EXPRESSION "FAIL!")
