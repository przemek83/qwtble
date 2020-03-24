# About project
 Library of useful plots and marker based on Qwt library. Created as a result of division of code of my other project named Volbx and moving parts of it to independent library. Library contains:  
 + quantiles plot
 + grouping plot
 + histogram plot
 + basic data plot 
 + grouping plot UI (quantiles plot + grouping plot + combo box)
 + histogram plot UI (histogram plot + line edit with intervals count)
 + notched marker
  
# Building
Clone and use Cmake directly or via QtCreator. Cmake **should**:
+ configure everything automatically,
+ compile library and create binaries.

**TIP**: remember to set properly `CMAKE_PREFIX_PATH` env variable. It should have Qt installation path to let Cmake `find_package` command work.  

As a result of compilation dynamic lib should be created along with headers dir.

To use it as external project via Cmake you may check how it is done in my other project called Volbx.

# Usage
Easiest way is to check examples subproject where you can find how to create and interact with each plot and notched marker.  
Alternatively tests subproject can be checked. Usage also can be found in my other project called Volbx where plots from this library are used.

# Plots
Set of plots based on Qwt library. Each plot can be used as a widget with data delivered via public slots and reactions emitted via signals. Each plot consist mechanisms like magnifying, navigating, resetting, displaying current coordinates and showing tool tip with summary after hovering mouse.
## Quantiles
![Alt text](QuantilesPlot.png?raw=true "Quantiles Plot")  
Plot showing quantiles (Q10, Q25, Q50, Q75, Q90) along with minimum, maximum and mean. Optionally small legend at left side might be drawn. Legend hides when size of plot is smaller than hardcoded pixel threshold.   
Number of items is displayed at the bottom.  
## Grouping
![Alt text](GroupingPlot.png?raw=true "Grouping plot")  
Plot showing quantiles (Q10, Q25, Q50, Q75, Q90) along with minimum, maximum and mean categorized according to trait. Example trait would be shape for geometrical figures or color for cars. At the bottom name of trait is displayed together with number of items. Details are displayed after hovering above each notched marker.  
Scales are drawn at the left and right edge of plot.
### Histogram
![Alt text](HistogramPlot.png?raw=true "Histogram plot")  
Plot showing histogram for given data. Number of intervals is configurable. Distribution and histogram can be enabled or disabled by clicking buttons at plot bottom.
### Basic data
![Alt text](BasicDataPlot.png?raw=true "Basic data plot")  
TODO
### Grouping with UI
![Alt text](GroupingPlotUI.png?raw=true "Grouping with UI")  
TODO
### Histogram with UI
![Alt text](QuantilesPlotUI.png?raw=true "Histogram with UI")  
TODO

# Markers
### Notched
![Alt text](NotchedMarker.png?raw=true "Notched marker")  
TODO
