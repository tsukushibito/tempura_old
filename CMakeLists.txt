cmake_minimum_required(VERSION 3.12)

project(tempura)

function(add_source_group)
    foreach(_source IN ITEMS ${ARGN})
        if (IS_ABSOLUTE ${_source})
            file(RELATIVE_PATH _source_rel ${CMAKE_CURRENT_SOURCE_DIR} ${_source})
        else()
            set(_source_rel "${_source}")
        endif()
        get_filename_component(_source_path ${_source_rel} DIRECTORY)
        string(REPLACE "/" "\\" _group "${_source_path}")
        source_group("${_group}" FILES "${_source}")
    endforeach()
endfunction(add_source_group)

add_subdirectory(engine)
add_subdirectory(application)