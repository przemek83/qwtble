if(MSVC)
    set(QWT_BUILD_COMMAND "nmake")
else()
    set(QWT_BUILD_COMMAND ${CMAKE_MAKE_PROGRAM})
endif()

set(PATCH_MARKER "${CMAKE_CURRENT_BINARY_DIR}/qwt_patch_applied.txt")
if (NOT EXISTS "${PATCH_MARKER}")
    set(QWT_PATCH_FILE ${CMAKE_CURRENT_SOURCE_DIR}/qwt.patch)
    message(STATUS "Using QWT_PATCH_FILE=${QWT_PATCH_FILE}")
    file(TOUCH ${PATCH_MARKER})
else()
    set(QWT_PATCH_FILE ${PATCH_MARKER})
    message(STATUS "Qwt patch already applied. Using empty file as QWT_PATCH_FILE=${PATCH_MARKER}")
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