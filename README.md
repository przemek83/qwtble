# About project
 Library of useful plots and marker based on QWT library. Created as a result of division of code of my other project named Volbx and moving parts of it to independent library. Library contains:  
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
