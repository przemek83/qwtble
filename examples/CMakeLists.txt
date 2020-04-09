project(examples)

set(${PROJECT_NAME}_SOURCES
    example.cpp
    )

add_executable(examples ${${PROJECT_NAME}_SOURCES})

target_link_libraries(examples PRIVATE Qt5::Core Qt5::Widgets qwtble)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE optimized qwt debug qwtd)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE qwt)
endif()


