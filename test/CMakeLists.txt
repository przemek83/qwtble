project(tests)

set(SOURCES
    Tests.cpp
    UtilitiesTest.cpp
    GroupPlotUITest.cpp
    QuantilesTest.cpp
)

set(HEADERS
    UtilitiesTest.h
    GroupPlotUITest.h
    QuantilesTest.h
)

add_executable(tests ${SOURCES} ${HEADERS})

target_link_libraries(tests PRIVATE qwtble Qt6::Test Qt6::Widgets)

add_test(NAME tests COMMAND tests)

