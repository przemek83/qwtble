cmake_minimum_required(VERSION 3.16)

project(qwtble
        LANGUAGES CXX
        VERSION 1.1.0
        DESCRIPTION "Library with widgets built on top of Qwt."
        HOMEPAGE_URL "https://github.com/przemek83/qwtble")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(CODE_COVERAGE "Collect coverage" OFF)

if(CODE_COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 --coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 --coverage")
endif()

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Test)
qt_standard_project_setup()

include(qwt_setup.cmake)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(${PROJECT_NAME}_SOURCES
    src/qwtble_global.h
    src/BasicDataPlot.h
    src/BasicDataPlot.cpp
    src/YAxisNumberPicker.h
    src/YAxisNumberPicker.cpp
    src/GroupPlot.h
    src/GroupPlot.cpp
    src/HistogramPlot.h
    src/HistogramPlot.cpp
    src/XYAxisNumberPicker.h
    src/XYAxisNumberPicker.cpp
    src/XDateYAxisNumberPicker.h
    src/XDateYAxisNumberPicker.cpp
    src/NotchedMarker.h
    src/NotchedMarker.cpp
    src/Picker.h
    src/Picker.cpp
    src/PlotBase.h
    src/PlotBase.cpp
    src/PlotMagnifier.h
    src/PlotMagnifier.cpp
    src/QuantilesPlot.h
    src/QuantilesPlot.cpp
    src/StringsScaleDraw.h
    src/StringsScaleDraw.cpp
    src/Quantiles.h
    src/Quantiles.cpp
    src/QwtBleUtilities.h
    src/QwtBleUtilities.cpp
    src/GroupPlotUI.h
    src/GroupPlotUI.cpp
    src/HistogramPlotUI.h
    src/HistogramPlotUI.cpp
    src/Utilities.h
    src/Utilities.cpp
)

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

set(UI
    src/GroupPlotUI.ui
    src/HistogramPlotUI.ui
)
source_group("UI Files" FILES ${UI})

add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_SOURCES} ${UI})

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER "${PUBLIC_HEADERS}")

configure_file(${PROJECT_NAME}.pc.in ${PROJECT_NAME}.pc @ONLY)

target_compile_definitions(${PROJECT_NAME} PRIVATE QWTBLE_LIBRARY)

install(TARGETS ${PROJECT_NAME} 
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets)
if (WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC optimized qwt debug qwtd)
else()
    target_link_libraries(${PROJECT_NAME} PUBLIC qwt)
endif()

add_subdirectory(examples)

enable_testing()
add_subdirectory(test)
