# Attention: This CMakeLists.txt implements the bare minimum of what is
#            required by SWEB.

cmake_minimum_required(VERSION 3.0.2)

set(CMAKE_CXX_STANDARD 11)

add_custom_command(
    OUTPUT to_string.cc
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/../elf/enum-print.py" "${CMAKE_CURRENT_BINARY_DIR}/../elf/enum-print.py"
    COMMAND make to_string.cc
    DEPENDS ../elf/enum-print.py dwarf++.hh data.hh Makefile internal.hh
)

add_library(dwarf++ STATIC
    dwarf.cc cursor.cc die.cc value.cc abbrev.cc
    expr.cc rangelist.cc line.cc attrs.cc
    die_str_map.cc elf.cc to_string.cc
)
