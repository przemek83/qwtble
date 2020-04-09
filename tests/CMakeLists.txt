project(tests)

set(${PROJECT_NAME}_SOURCES
    Tests.cpp
    UtilitiesTest.cpp
    UtilitiesTest.h
    GroupPlotUITest.cpp
    GroupPlotUITest.h
    QuantilesTest.cpp
    QuantilesTest.h
    )

add_executable(tests ${${PROJECT_NAME}_SOURCES})

target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(tests PRIVATE Qt5::Test Qt5::Core Qt5::Widgets qwtble)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE optimized qwt debug qwtd)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE qwt)
endif()

add_test(NAME tests COMMAND tests)

