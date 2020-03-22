cmake_minimum_required(VERSION 3.8)

project(qwtble LANGUAGES CXX VERSION 0.0.1 DESCRIPTION "Library with widgets built on top of Qwt.")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt5 COMPONENTS Widgets Core Test REQUIRED)
add_definitions( ${QT_DEFINITIONS} )

# QWT
if(DEFINED ENV{QWT_ROOT})
    message(STATUS "QWT_ROOT environment variable defined, using QWT_ROOT paths.")
    set(QWT_INCLUDE_PATH $ENV{QWT_ROOT}/include)
    set(QWT_BINARY_PATH $ENV{QWT_ROOT}/lib)
else()
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
endif()

message(STATUS "Using QWT_INCLUDE_PATH ${QWT_INCLUDE_PATH}")
message(STATUS "Using QWT_BINARY_PATH ${QWT_BINARY_PATH}")

include_directories(${QWT_INCLUDE_PATH})
LINK_DIRECTORIES(${QWT_BINARY_PATH})

add_library(${PROJECT_NAME} SHARED
  src/qwtble_global.h
  src/BasicDataPlot.cpp
  src/BasicDataPlot.h
  src/YAxisNumberPicker.cpp
  src/YAxisNumberPicker.h
  src/GroupPlot.cpp
  src/GroupPlot.h
  src/HistogramPlot.cpp
  src/HistogramPlot.h
  src/XYAxisNumberPicker.cpp
  src/XYAxisNumberPicker.h
  src/XDateYAxisNumberPicker.cpp
  src/XDateYAxisNumberPicker.h
  src/NotchedMarker.cpp
  src/NotchedMarker.h
  src/Picker.cpp
  src/Picker.h
  src/PlotBase.cpp
  src/PlotBase.h
  src/PlotMagnifier.cpp
  src/PlotMagnifier.h
  src/QuantilesPlot.cpp
  src/QuantilesPlot.h
  src/StringsScaleDraw.cpp
  src/StringsScaleDraw.h
  src/Quantiles.cpp
  src/Quantiles.h
  src/QwtBleUtilities.cpp
  src/QwtBleUtilities.h
  src/GroupPlotUI.cpp
  src/GroupPlotUI.h
  src/GroupPlotUI.ui
  src/HistogramPlotUI.cpp
  src/HistogramPlotUI.h
  src/HistogramPlotUI.ui
  src/ScrollArea.cpp
  src/ScrollArea.h
)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION 1)

set_property(TARGET ${PROJECT_NAME} PROPERTY PUBLIC_HEADER
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
target_include_directories(${PROJECT_NAME} PUBLIC src)
include(GNUInstallDirs)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Widgets optimized qwt debug qwtd)

target_compile_definitions(${PROJECT_NAME} PRIVATE QWTBLE_LIBRARY)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                           ${CMAKE_BINARY_DIR}/libqwtble.dll
                           ${CMAKE_BINARY_DIR}/examples/libqwtble.dll)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                           ${CMAKE_BINARY_DIR}/libqwtble.dll
                           ${CMAKE_BINARY_DIR}/tests/libqwtble.dll)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                           ${QWT_BINARY_PATH}/qwt.dll
                           ${CMAKE_BINARY_DIR}/tests/qwt.dll)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                           ${QWT_BINARY_PATH}/qwtd.dll
                           ${CMAKE_BINARY_DIR}/tests/qwtd.dll)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                           ${QWT_BINARY_PATH}/qwt.dll
                           ${CMAKE_BINARY_DIR}/examples/qwt.dll)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                           ${QWT_BINARY_PATH}/qwtd.dll
                           ${CMAKE_BINARY_DIR}/examples/qwtd.dll)

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

add_subdirectory(examples)

enable_testing()
add_subdirectory(tests)


