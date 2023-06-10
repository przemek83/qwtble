## Table of content
- [About project](#about-project)
- [Building](#building)
- [Usage](#usage)
- [Plots](#plots)
- [Markers](#markers)


# About project
 Library of useful plots and one marker based on Qwt library. Created as a result of division of code of my other project named Volbx and moving parts of it to independent library. Library contains:  
 + quantiles plot,
 + grouping plot,
 + histogram plot,
 + basic data plot,
 + grouping plot UI (quantiles plot + grouping plot + combo box),
 + histogram plot UI (histogram plot + line edit with intervals count),
 + notched marker.
  
# Building
Clone and use CMake directly or via IDE like Qt Creator. CMake **should**:
+ configure everything automatically,
+ detect installation of Qwt (using environment variable QWT_ROOT) or download it and build,
+ compile library and create binaries.

**TIP**: remember to set properly `CMAKE_PREFIX_PATH` env variable to let CMake `find_package` command work. It should have Qt installation path.  

As a result of compilation, dynamic lib should be created along with headers dir.

Check my other project called Volbx to familiarize yourself how to use it via CMake.

## Used tools and libs
| Tool |  Windows | Lubuntu |
| --- | --- | --- |
| OS version | 10 22H2 | 22.04 |
| GCC | 8.1.0 | 9.5.0 |
| CMake | 3.25.0 | 3.25.0 |
| Git | 2.38.1 | 2.34.1 |
| SVN | 1.14.2 | 1.14.1 |
| Qt | 5.15.2 | 5.15.2 |
| Qt Creator | 9.0.0 |9.0.0 |
| Qwt | 6.1.6 | 6.1.6 |


# Usage
The easiest way is to check examples subproject, where you can find how to create and interact with each plot and notched marker.  
Alternatively, tests subproject can be checked. Usage also can be found in my other project called Volbx where plots from this library are used.

# Plots
Set of plots based on Qwt library. Each plot can be used as a widget with data delivered via public slot. Grouping plot UI additionally interact with calling code via one signal. Each plot consist of mechanisms like magnifying, navigating, resetting, displaying current coordinates and showing tool tip with summary after hovering mouse.
## Quantiles
![Alt text](QuantilesPlot.png?raw=true "Quantiles Plot")  
Plot showing quantiles (Q10, Q25, Q50, Q75, Q90) along with minimum, maximum and mean. Optionally, a small legend on the left side can be activated. Legend hides when the size of the plot is smaller than the hard-coded pixel threshold.   
The number of items is displayed at the bottom.  
## Grouping
![Alt text](GroupingPlot.png?raw=true "Grouping plot")  
Plot showing quantiles (Q10, Q25, Q50, Q75, Q90) along with minimum, maximum and mean categorized according to trait type. 
Trait example would be shape for geometrical figures or color for cars. The name of trait is displayed at the bottom together with the number of items. Details are displayed after hovering above each notched marker.  
Scales are drawn at the left and right edge of the plot.
### Histogram
![Alt text](HistogramPlot.png?raw=true "Histogram plot")  
Plot showing histogram for given data. Number of intervals is configurable. Distribution and histogram can be enabled or disabled by clicking buttons at the plot bottom.
### Basic data
![Alt text](BasicDataPlot.png?raw=true "Basic data plot")  
Plot showing data series in form of dots. Dates are placed on x-axis, values on y-axis. Except of raw data, there are also displayed curves for:
+ Q25,
+ Q50,
+ Q75,
+ linear regression.

Each part of plot can be enabled or disabled using buttons at the bottom.
### Grouping with UI
![Alt text](GroupingPlotUI.png?raw=true "Grouping with UI")  
Quantiles and grouping plot packed together along with combo box for picking trait. Quantiles plot is showing summary data, each notched marker on the group plot is showing quantiles for each trait type. The proportion of area used for each plot can be changed by dragging the handle, placed between plots. Dragging the handle to any side results in hiding one of the plots. 
### Histogram with UI
![Alt text](QuantilesPlotUI.png?raw=true "Histogram with UI")  
Histogram plot paired with spin box. Changing value on spin box results in changing number of intervals used for histogram.

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

Can be used to show one or multiple sets of data on one plot. Check quantiles and grouping plots for usage example. 