
cmake_minimum_required(VERSION 3.16)

function(QWT_SETUP)
    if(MSVC)
        set(QWT_BUILD_COMMAND "nmake")
    else()
        set(QWT_BUILD_COMMAND ${CMAKE_MAKE_PROGRAM})
    endif()

    configure_file(CMakeLists.txt.qwt qwt/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/qwt)
    execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/qwt)

    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/qwt/install)
    file(COPY ${CMAKE_CURRENT_BINARY_DIR}/qwt/qwt/src/qwt-build/lib DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/qwt/install)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/qwt/install/include)
    file(GLOB QWT_HEADERS "${CMAKE_CURRENT_BINARY_DIR}/qwt/qwt/src/qwt/src/*.h")
    file(COPY ${QWT_HEADERS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/qwt/install/include)
    set(QWT_INCLUDE_PATH ${CMAKE_CURRENT_BINARY_DIR}/qwt/install/include)
    set(QWT_BINARY_PATH ${CMAKE_CURRENT_BINARY_DIR}/qwt/install/lib)

    message(STATUS "Using QWT_INCLUDE_PATH ${QWT_INCLUDE_PATH}")
    message(STATUS "Using QWT_BINARY_PATH ${QWT_BINARY_PATH}")

    include_directories(${QWT_INCLUDE_PATH})
    link_directories(${QWT_BINARY_PATH})
endfunction()

qwt_setup()
