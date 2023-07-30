project(examples)

set(SOURCES
    example.cpp
)

add_executable(examples ${SOURCES})

target_link_libraries(examples PRIVATE Qt6::Core Qt6::Widgets qwtble)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE optimized qwt debug qwtd)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE qwt)
endif()


