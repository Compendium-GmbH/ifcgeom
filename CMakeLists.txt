cmake_minimum_required(VERSION 3.17)
project(ifcgeom)

include(cmake/pkg.cmake)

option(IFCGEOM_LINT "Run clang-tidy with the compiler." OFF)
if (IFCGEOM_LINT)
  include(cmake/clang-tidy.cmake)
endif ()

express2cpp(deps/express2cpp/express/test/ifc23.txt ifc2x3)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(ifcgeom-compile-flags
      -Wno-global-constructors
      -Wno-exit-time-destructors
      -fno-strict-aliasing
      -Weverything
      -Wno-c++98-compat
      -Wno-c++98-compat-pedantic
      -Wno-newline-eof
      -Wno-missing-prototypes
      -Wno-padded
      -Wno-double-promotion
      -Wno-undef
      -Wno-undefined-reinterpret-cast
      -Wno-float-conversion
      -Wno-return-std-move-in-c++11
      -Wno-gnu-zero-variadic-macro-arguments
      -Wno-unknown-pragmas
      -Wno-documentation-unknown-command
      -Werror
      )
endif ()


# LIB
file(GLOB_RECURSE ifcgeom-files src/*.cc)
add_library(ifcgeom ${ifcgeom-files})
target_include_directories(ifcgeom PUBLIC include)
target_link_libraries(ifcgeom boost boost-filesystem utl cista ifc2x3 CGAL gmp mpfr)
target_compile_features(ifcgeom PUBLIC cxx_std_17)

# EXE
add_executable(compare-convex-hull exe/compare_convex_hulls.cc)
target_compile_options(compare-convex-hull PRIVATE ${ifcgeom-compile-flags})
target_link_libraries(compare-convex-hull ifcgeom)
target_compile_features(compare-convex-hull PUBLIC cxx_std_17)

add_executable(list-geometry-types exe/list_geometry_types.cc)
target_compile_options(list-geometry-types PRIVATE ${ifcgeom-compile-flags})
target_link_libraries(list-geometry-types ifcgeom)
target_compile_features(list-geometry-types PUBLIC cxx_std_17)

add_executable(scan-render-errors exe/scan_render_errors.cc)
target_compile_options(scan-render-errors PRIVATE ${ifcgeom-compile-flags})
target_link_libraries(scan-render-errors ifcgeom)
target_compile_features(scan-render-errors PUBLIC cxx_std_17)

add_executable(compare-geom exe/compare_geom.cc)
target_compile_options(compare-geom PRIVATE ${ifcgeom-compile-flags})
target_link_libraries(compare-geom ifcgeom)
target_compile_features(compare-geom PUBLIC cxx_std_17)

# TEST
file(GLOB_RECURSE ifcgeom-test-files test/*.cc)
add_executable(ifcgeom-test ${ifcgeom-test-files})
target_compile_options(ifcgeom-test PRIVATE ${ifcgeom-compile-flags})
target_link_libraries(ifcgeom-test doctest ifcgeom)
target_compile_features(ifcgeom-test PUBLIC cxx_std_17)
