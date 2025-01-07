SET(PROJECT_TESTS ${PROJECT_NAME}-tests)

set(${PROJECT_TESTS}_SOURCES
    Tests.cpp
    UtilitiesTest.h
    UtilitiesTest.cpp
    GroupPlotUITest.h
    GroupPlotUITest.cpp
    QuantilesTest.h
    QuantilesTest.cpp
    BasicDataPlotTest.h
    BasicDataPlotTest.cpp
)

qt_add_resources(${PROJECT_TESTS}_SOURCES testResources.qrc)
    
add_executable(${PROJECT_TESTS} ${${PROJECT_TESTS}_SOURCES})
target_link_libraries(${PROJECT_TESTS} PRIVATE qwtble Qt6::Test Qt6::Widgets)

if (WIN32)
    add_custom_command(TARGET ${PROJECT_TESTS} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_BINARY_DIR}/../qwt/install/lib" "$<TARGET_FILE_DIR:${PROJECT_TESTS}>")
endif()

add_test(NAME ${PROJECT_TESTS} COMMAND ${PROJECT_TESTS})
set_property(TEST ${PROJECT_TESTS} PROPERTY FAIL_REGULAR_EXPRESSION "FAIL!")
