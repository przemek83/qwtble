cmake_minimum_required(VERSION 3.16)

project(qwtble
        LANGUAGES CXX
        VERSION 1.1.0
        DESCRIPTION "Library with widgets built on top of Qwt."
        HOMEPAGE_URL "https://github.com/przemek83/qwtble")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Test)
qt_standard_project_setup()
message(STATUS ${CMAKE_GENERATOR})
if (CMAKE_MAKE_PROGRAM MATCHES "nmake")
    message(STATUS "Using NMake")
elseif (CMAKE_MAKE_PROGRAM MATCHES "mingw32-make")
    message(STATUS "Using MinGW Make")
elseif (CMAKE_MAKE_PROGRAM MATCHES "make")
    message(STATUS "Using Unix Make")
else()
    message(STATUS "Unknown Make tool")
endif()

# QWT
# if(DEFINED ENV{QWT_ROOT})
#     message(STATUS "QWT_ROOT environment variable defined, using QWT_ROOT paths.")
#     set(QWT_INCLUDE_PATH $ENV{QWT_ROOT}/include)
#     set(QWT_BINARY_PATH $ENV{QWT_ROOT}/lib)
# else()
    if(MSVC)
        set(QWT_BUILD_COMMAND "nmake")
    else()
        set(QWT_BUILD_COMMAND ${CMAKE_MAKE_PROGRAM})
    endif()

    configure_file(CMakeLists.txt.qwt qwt/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/qwt)
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/qwt)
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/qwt/install)
    file(COPY ${CMAKE_BINARY_DIR}/qwt/qwt/src/qwt-build/lib DESTINATION ${CMAKE_BINARY_DIR}/qwt/install)
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/qwt/install/include)
    file(GLOB QWT_HEADERS "${CMAKE_BINARY_DIR}/qwt/qwt/src/qwt/src/*.h" )
    file(COPY ${QWT_HEADERS} DESTINATION ${CMAKE_BINARY_DIR}/qwt/install/include)
    set(QWT_INCLUDE_PATH ${CMAKE_BINARY_DIR}/qwt/install/include)
    set(QWT_BINARY_PATH ${CMAKE_BINARY_DIR}/qwt/install/lib)
# endif()

message(STATUS "Using QWT_INCLUDE_PATH ${QWT_INCLUDE_PATH}")
message(STATUS "Using QWT_BINARY_PATH ${QWT_BINARY_PATH}")

include_directories(${QWT_INCLUDE_PATH})
link_directories(${QWT_BINARY_PATH})

set(SOURCES
    src/BasicDataPlot.cpp
    src/YAxisNumberPicker.cpp
    src/GroupPlot.cpp
    src/HistogramPlot.cpp
    src/XYAxisNumberPicker.cpp
    src/XDateYAxisNumberPicker.cpp
    src/NotchedMarker.cpp
    src/Picker.cpp
    src/PlotBase.cpp
    src/PlotMagnifier.cpp
    src/QuantilesPlot.cpp
    src/StringsScaleDraw.cpp
    src/Quantiles.cpp
    src/QwtBleUtilities.cpp
    src/GroupPlotUI.cpp
    src/HistogramPlotUI.cpp
    src/Utilities.cpp
)

set(HEADERS
    src/qwtble_global.h
    src/BasicDataPlot.h
    src/YAxisNumberPicker.h
    src/GroupPlot.h
    src/HistogramPlot.h
    src/XYAxisNumberPicker.h
    src/XDateYAxisNumberPicker.h
    src/NotchedMarker.h
    src/Picker.h
    src/PlotBase.h
    src/PlotMagnifier.h
    src/QuantilesPlot.h
    src/StringsScaleDraw.h
    src/Quantiles.h
    src/QwtBleUtilities.h
    src/GroupPlotUI.h
    src/HistogramPlotUI.h
    src/Utilities.h
)

set(UI
    src/GroupPlotUI.ui
    src/HistogramPlotUI.ui
)
source_group("UI Files" FILES ${UI})

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS} ${UI})

set(PUBLIC_HEADERS
    src/qwtble_global.h
    src/BasicDataPlot.h
    src/GroupPlot.h
    src/HistogramPlot.h
    src/PlotBase.h
    src/QuantilesPlot.h
    src/Quantiles.h
    src/QwtBleUtilities.h
    src/NotchedMarker.h
    src/GroupPlotUI.h
    src/HistogramPlotUI.h
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER "${PUBLIC_HEADERS}"
)

target_include_directories(${PROJECT_NAME} PUBLIC src)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets)
if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE optimized qwt debug qwtd)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE qwt)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE QWTBLE_LIBRARY)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

add_subdirectory(examples)

enable_testing()
add_subdirectory(tests)
