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
Clone and use Cmake directly or via IDE like QtCreator. Cmake **should**:
+ configure everything automatically,
+ detect installation of Qwt (using environment variable QWT_ROOT) or download it and build,
+ compile library and create binaries.

**TIP**: remember to set properly `CMAKE_PREFIX_PATH` env variable to let Cmake `find_package` command work. It should have Qt installation path.  

As a result of compilation dynamic lib should be created along with headers dir.

To use it as external project via Cmake you may check how it is done in my other project called Volbx.

# Usage
Easiest way is to check examples subproject where you can find how to create and interact with each plot and notched marker.  
Alternatively tests subproject can be checked. Usage also can be found in my other project called Volbx where plots from this library are used.

# Plots
Set of plots based on Qwt library. Each plot can be used as a widget with data delivered via public slot. Grouping plot UI additionally interact with calling code via one signal. Each plot consist mechanisms like magnifying, navigating, resetting, displaying current coordinates and showing tool tip with summary after hovering mouse.
## Quantiles
![Alt text](QuantilesPlot.png?raw=true "Quantiles Plot")  
Plot showing quantiles (Q10, Q25, Q50, Q75, Q90) along with minimum, maximum and mean. Optionally small legend at left side can be activated. Legend hides when size of plot is smaller than hardcoded pixel threshold.   
Number of items is displayed at the bottom.  
## Grouping
![Alt text](GroupingPlot.png?raw=true "Grouping plot")  
Plot showing quantiles (Q10, Q25, Q50, Q75, Q90) along with minimum, maximum and mean categorized according to trait type. 
Trait example would be shape for geometrical figures or color for cars. Name of trait is displayed at the bottom together with number of items. Details are displayed after hovering above each notched marker.  
Scales are drawn at the left and right edge of plot.
### Histogram
![Alt text](HistogramPlot.png?raw=true "Histogram plot")  
Plot showing histogram for given data. Number of intervals is configurable. Distribution and histogram can be enabled or disabled by clicking buttons at plot bottom.
### Basic data
![Alt text](BasicDataPlot.png?raw=true "Basic data plot")  
Plot showing data series in form of dots. Dates are placed on x axis, values on y axis. Except of raw data there are also displayed curves for:
+ Q25,
+ Q50,
+ Q75,
+ linear regression.

Each part of plot can be enabled or disabled using buttons at bottom.
### Grouping with UI
![Alt text](GroupingPlotUI.png?raw=true "Grouping with UI")  
Quantiles and grouping plot packed together along with combo box for picking trait. Quantiles plot is showing summary data, each notched marker on group plot is showing quantiles for each trait type. Proportion of area used for each plot can be changed by dragging handle placed between plots. Dragging handle to any side results in hiding one of plots. 
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