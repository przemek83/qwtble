
cmake_minimum_required(VERSION 3.16)

# Rewrite qwtconfig.pri inplace dropping commented lines and  commenting all 
# lines having one of given keywords. Compile only neded by project files.
function(CONFIGURE_QWT)
    file(STRINGS "${CMAKE_BINARY_DIR}/qwtconfig.pri" inputLines)

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
    file(WRITE "${CMAKE_BINARY_DIR}/qwtconfig.pri" "${outputContent}")
endfunction()

configure_qwt()
