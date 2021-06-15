cmake_minimum_required(VERSION 3.17)
project(ifcgeom)

include(cmake/pkg.cmake)

add_library(ifcgeom INTERFACE)
target_include_directories(ifcgeom INTERFACE include)
target_link_libraries(ifcgeom INTERFACE ifctools CGAL)
target_compile_features(ifcgeom INTERFACE cxx_std_17)