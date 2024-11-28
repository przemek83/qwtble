
cmake_minimum_required(VERSION 3.16)

# Rewrite qwtconfig.pri inplace dropping commented lines and compile only 
# neded by project files by commenting all lines having one of given keywords. 
# Set building mode to static library.
function(CONFIGURE_QWT)
    file(STRINGS "${CMAKE_CURRENT_BINARY_DIR}/qwtconfig.pri" inputLines)

    set(keywords "QwtExamples" "QwtPlayground" "QwtTests" "QwtDesignerSelfContained" "QwtDesigner" "QwtPolar" "QwtSvg" "QwtDll")
    set(modifiedLines)
    foreach(line IN LISTS inputLines)
        if("${line}" MATCHES "^[ \t]*#")
            continue() 
        endif()

        foreach(keyword IN LISTS keywords) 
            if("${line}" MATCHES ".*${keyword}.*") 
                set(line "# ${line}")
                break() 
            endif() 
        endforeach()

        list(APPEND modifiedLines "${line}")
    endforeach()

    string(REPLACE ";" "\n" outputContent "${modifiedLines}")
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/qwtconfig.pri" "${outputContent}")
endfunction()

configure_qwt()
