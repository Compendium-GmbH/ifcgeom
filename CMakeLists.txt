cmake_minimum_required(VERSION 3.17)
project(ifcgeom)

include(cmake/pkg.cmake)

if (NOT TARGET ifc2x3)
    express2cpp(deps/express2cpp/express/test/ifc23.txt ifc2x3)
endif ()

# LIB
add_library(ifcgeom INTERFACE)
target_include_directories(ifcgeom INTERFACE include ifc2x3)
target_link_libraries(ifcgeom INTERFACE boost boost-filesystem utl cista ifc2x3 CGAL gmp mpfr)
target_compile_features(ifcgeom INTERFACE cxx_std_17)

# EXE
add_executable(compare-convex-hull exe/compare_convex_hulls.cc)
target_link_libraries(compare-convex-hull ifcgeom)
target_compile_features(compare-convex-hull PUBLIC cxx_std_17)

add_executable(list-geometry-types exe/list_geometry_types.cc)
target_link_libraries(list-geometry-types ifcgeom)
target_compile_features(list-geometry-types PUBLIC cxx_std_17)

add_executable(scan-render-errors exe/scan_render_errors.cc)
target_link_libraries(scan-render-errors ifcgeom)
target_compile_features(scan-render-errors PUBLIC cxx_std_17)

# TEST
file(GLOB_RECURSE ifcgeom-test-files test/*.cc)
add_executable(ifcgeom-test ${ifcgeom-test-files})
target_link_libraries(ifcgeom-test doctest ifcgeom)
target_compile_features(ifcgeom-test PUBLIC cxx_std_17)
