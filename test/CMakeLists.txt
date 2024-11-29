SET(PROJECT_TEST ${PROJECT_NAME}-test )

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

add_test(NAME ${PROJECT_TEST} COMMAND ${PROJECT_TEST})
