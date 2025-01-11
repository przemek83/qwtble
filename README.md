[![Build & test](https://github.com/przemek83/qwtble/actions/workflows/buld-and-test.yml/badge.svg)](https://github.com/przemek83/qwtble/actions/workflows/buld-and-test.yml)
[![CodeQL](https://github.com/przemek83/qwtble/actions/workflows/codeql.yml/badge.svg)](https://github.com/przemek83/qwtble/actions/workflows/codeql.yml)
[![codecov](https://codecov.io/gh/przemek83/qwtble/graph/badge.svg?token=UJY24KQANL)](https://codecov.io/gh/przemek83/qwtble)

[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=przemek83_qwtble&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=przemek83_qwtble)
[![Bugs](https://sonarcloud.io/api/project_badges/measure?project=przemek83_qwtble&metric=bugs)](https://sonarcloud.io/summary/new_code?id=przemek83_qwtble)
[![Code Smells](https://sonarcloud.io/api/project_badges/measure?project=przemek83_qwtble&metric=code_smells)](https://sonarcloud.io/summary/new_code?id=przemek83_qwtble)
[![Coverage](https://sonarcloud.io/api/project_badges/measure?project=przemek83_qwtble&metric=coverage)](https://sonarcloud.io/summary/new_code?id=przemek83_qwtble)
[![Duplicated Lines (%)](https://sonarcloud.io/api/project_badges/measure?project=przemek83_qwtble&metric=duplicated_lines_density)](https://sonarcloud.io/summary/new_code?id=przemek83_qwtble)

## Table of content
- [About project](#about-project)
- [Building](#building)
- [Usage](#usage)
- [Plots](#plots)
- [Markers](#markers)

## About project
 Qwtble is a library of useful plots and one marker based on Qwt library. Created as a result of the division of the code of my other project, Volbx and moving parts of it to an independent library. Library contains:  
 + quantiles plot,
 + grouping plot,
 + histogram plot,
 + basic data plot,
 + grouping plot UI (quantiles plot + grouping plot + combo box),
 + histogram plot UI (histogram plot + line edit with intervals count),
 + notched marker.

## Getting Started
This section describes briefly how to setup the environment and build the project.

### Prerequisites
Qt in version 6.5 or greater, a C++ compiler with C++17 support as a minimum, and CMake 3.16+. 

### Building
Clone and use CMake directly or via any IDE supporting it. CMake should:
- configure everything automatically,
- compile and create binaries.

As a result of compilation, binary for simulations and binary for testing should be created.

**TIP**: Remember to set properly the `CMAKE_PREFIX_PATH` env variable. It should have a Qt installation path to let CMake `find_package` command work.  

**TIP**: Make sure you install the `Core5Compat` module, which is part of Qt 6 as QuaZip needs it.  

### CMake integration
Use `FetchContent` CMake module in your project:
```cmake
include(FetchContent)

FetchContent_Declare(
   qwtble
   GIT_REPOSITORY https://github.com/przemek83/qwtble
   GIT_TAG v1.2.0
)

FetchContent_MakeAvailable(qwtble)
```
From that moment, qwtble library can be used in the `target_link_libraries` command:
```cmake
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} shared qwtble)
```
Check my other project `Volbx` for real world CMake integration.

## Built with
| Tool |  Windows | Ubuntu |
| --- | --- | --- |
| OS version | 10 22H2 | 24.04 |
| GCC | 13.1.0 | 13.2.0 |
| CMake | 3.30.2 | 3.28.3 |
| Git | 2.46.0 | 2.43.0 |
| Qt | 6.5.2 | 6.5.2 |
| Qwt | 6.3.1 | 6.3.1 |

## Usage
The easiest way is to check the examples' subproject, where you can find how to create and interact with each plot and notched marker.  
Alternatively, tests in a subproject can be checked. Usage can also be found in my other project called Volbx where plots from this library are used.

## Plots
Set of plots based on Qwt library. Each plot can be used as a widget, with data delivered via a public slot. The grouping plot UI additionally interacts with the calling code via one signal. Each plot consists of mechanisms like magnifying, navigating, resetting, displaying current coordinates, and showing a tooltip with a summary after hovering the mouse.

### Quantiles
![Alt text](QuantilesPlot.png?raw=true "Quantiles Plot")  
Plot showing quantiles (Q10, Q25, Q50, Q75, Q90) along with minimum, maximum and mean. Optionally, a small legend on the left side can be activated. Legend hides when the size of the plot is smaller than the hard-coded pixel threshold.   
The number of items is displayed at the bottom.

### Grouping
![Alt text](GroupingPlot.png?raw=true "Grouping plot")  
Plot showing quantiles (Q10, Q25, Q50, Q75, Q90) along with minimum, maximum and mean categorized according to trait type. 
A trait example would be shape for geometrical figures or color for cars. The name of the trait is displayed at the bottom, together with the number of items. Details are displayed after hovering above each notched marker.  
Scales are drawn at the left and right edges of the plot.

### Histogram
![Alt text](HistogramPlot.png?raw=true "Histogram plot")  
Plot showing the histogram for the given data. The number of intervals is configurable. Distribution and histograms can be enabled or disabled by clicking buttons at the plot bottom.

### Basic data
![Alt text](BasicDataPlot.png?raw=true "Basic data plot")  
Plot showing data series in the form of dots. Dates are placed on the x-axis and values on the y-axis. Except for raw data, there are also displayed curves for:
+ Q25,
+ Q50,
+ Q75,
+ linear regression.

Each part of the plot can be enabled or disabled using buttons at the bottom.

### Grouping with UI
![Alt text](GroupingPlotUI.png?raw=true "Grouping with UI")  
Quantiles and grouping plots are packed together, along with a combo box for picking traits. The quantiles plot is showing summary data; each notched marker on the group plot is showing quantiles for each trait type. The proportion of area used for each plot can be changed by dragging the handle, placed between plots. Dragging the handle to any side results in hiding one of the plots.

### Histogram with UI
![Alt text](QuantilesPlotUI.png?raw=true "Histogram with UI")  
Histogram plot paired with a spin box. Changing the value on the spin box results in changing the number of intervals used for the histogram.

## Markers
### Notched
![Alt text](NotchedMarker.png?raw=true "Notched marker")  
Marker showing:
+ Q10,
+ Q25,
+ Q50,
+ Q75,
+ Q90,
+ minimum,
+ maximum,
+ mean.

Can be used to show one or multiple sets of data on one plot. Check quantiles and grouping plots for usage examples. 

## Testing
For testing purposes, the Qt Test framework is used. Build the project first. Make sure that the `qwtble-tests` target is built. Modern IDEs supporting CMake also support running tests with monitoring of failures. But in case you would like to run it manually, go to the `build/tests` directory, where the⁣ binary `qwtble-tests` should be available. Launching it should produce the following output on Linux:
Example run:
```
$ $ ./qwtble-tests
********* Start testing of UtilitiesTest *********
Config: Using QtTest library 6.5.2, Qt 6.5.2 (x86_64-little_endian-lp64 shared (dynamic) release build; by GCC 10.3.1 20210422 (Red Hat 10.3.1-1)), ubuntu 24.04
PASS   : UtilitiesTest::initTestCase()
PASS   : UtilitiesTest::testStringFromDays()
PASS   : UtilitiesTest::testFloatsAreEqual()

(...)

PASS   : QuantilesPlotTest::testReset()
PASS   : QuantilesPlotTest::cleanupTestCase()
Totals: 5 passed, 0 failed, 0 skipped, 0 blacklisted, 85ms
********* Finished testing of QuantilesPlotTest *********

```
As an alternative, CTest can be used to run tests from the `build/tests` directory:
```
$ ctest
Test project <path>/qwtble/build/tests
    Start 1: qwtble-tests
1/1 Test #1: qwtble-tests .....................   Passed    0.25 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.25 sec

```

## Licensing
Qwtble library is published under a LGPL license.

The project uses the following software:
| Name | License | Home | Description |
| --- | --- | --- | --- |
| Qt | LGPLv3 | https://www.qt.io/| cross-platform application development framework |
| Qwt | Qwt License 1.0 | https://qwt.sourceforge.io/ | Qt widgets for technical applications |

Testing subproject uses following software:
| Name | License | Home | Description |
| --- | --- | --- | --- |
| Fira font | SIL Open Font License 1.1| https://github.com/mozilla/Fira | Mozilla's Fira type family |