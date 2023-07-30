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

target_link_libraries(tests PRIVATE Qt6::Test Qt6::Core Qt6::Widgets qwtble)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE optimized qwt debug qwtd)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE qwt)
endif()

add_test(NAME tests COMMAND tests)

