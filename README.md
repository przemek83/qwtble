[![Build & test](https://github.com/przemek83/qwtble/actions/workflows/buld-and-test.yml/badge.svg)](https://github.com/przemek83/qwtble/actions/workflows/buld-and-test.yml)
[![CodeQL](https://github.com/przemek83/qwtble/actions/workflows/codeql.yml/badge.svg)](https://github.com/przemek83/qwtble/actions/workflows/codeql.yml)

## Table of content
- [About project](#about-project)
- [Building](#building)
- [Usage](#usage)
- [Plots](#plots)
- [Markers](#markers)


# About project
 Qwtble is a library of useful plots and one marker based on Qwt library. Created as a result of the division of the code of my other project, Volbx and moving parts of it to an independent library. Library contains:  
 + quantiles plot,
 + grouping plot,
 + histogram plot,
 + basic data plot,
 + grouping plot UI (quantiles plot + grouping plot + combo box),
 + histogram plot UI (histogram plot + line edit with intervals count),
 + notched marker.
  
# Building
Clone and use CMake directly or via an IDE like Qt Creator. CMake **should**:
+ configure everything automatically,
+ detect installation of Qwt (using environment variable QWT_ROOT) or download it and build,
+ compile library and create binaries.

**TIP**: remember to set properly `CMAKE_PREFIX_PATH` env variable to let CMake `find_package` command work. It should have a Qt installation path.  

As a result of compilation, a dynamic lib should be created along with a headers' dir.

Check out my other project, Volbx to familiarize yourself with how to use it via CMake.

## Used tools and libs
| Tool |  Windows | Lubuntu |
| --- | --- | --- |
| OS version | 10 22H2 | 22.04 |
| GCC | 11.2.0 | 11.3.0 |
| CMake | 3.25.0 | 3.25.0 |
| Git | 2.38.1 | 2.34.1 |
| Qt | 6.5.2 | 6.5.2 |
| Qt Creator | 10.0.2 | 10.0.2 |
| Qwt | 6.2 | 6.2 |


# Usage
The easiest way is to check the examples' subproject, where you can find how to create and interact with each plot and notched marker.  
Alternatively, tests in a subproject can be checked. Usage can also be found in my other project called Volbx where plots from this library are used.

# Plots
Set of plots based on Qwt library. Each plot can be used as a widget, with data delivered via a public slot. The grouping plot UI additionally interacts with the calling code via one signal. Each plot consists of mechanisms like magnifying, navigating, resetting, displaying current coordinates, and showing a tooltip with a summary after hovering the mouse.
## Quantiles
![Alt text](QuantilesPlot.png?raw=true "Quantiles Plot")  
Plot showing quantiles (Q10, Q25, Q50, Q75, Q90) along with minimum, maximum and mean. Optionally, a small legend on the left side can be activated. Legend hides when the size of the plot is smaller than the hard-coded pixel threshold.   
The number of items is displayed at the bottom.  
## Grouping
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

# Markers
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
