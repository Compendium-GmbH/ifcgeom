#include "doctest/doctest.h"

#include <vector>

#include "CGAL/Polygon_mesh_processing/corefinement.h"
#include "CGAL/Polygon_mesh_processing/measure.h"

#include "CGAL/convex_hull_3.h"

#include "ifcgeom/core/context.h"

void check_boolean(ifcgeom::Nef_Polyhedron_3 const& p, unsigned i) {
  REQUIRE(!p.is_empty());
  ifcgeom::Polyhedron_3 polyhedron;
  p.convert_to_Polyhedron(polyhedron);
  auto vol = CGAL::Polygon_mesh_processing::volume(polyhedron);
  CHECK(static_cast<unsigned>(vol) == i);
}
void check_boolean(ifcgeom::Mesh const& m, unsigned i) {
  REQUIRE(!m.is_empty());
  auto vol = CGAL::Polygon_mesh_processing::volume(m);
  CHECK(static_cast<unsigned>(vol) == i);
}

std::vector<ifcgeom::Point_3> const vec_1{
    ifcgeom::Point_3{0, 0, 0}, ifcgeom::Point_3{3, 0, 0},
    ifcgeom::Point_3{3, 3, 0}, ifcgeom::Point_3{0, 3, 0},
    ifcgeom::Point_3{0, 0, 3}, ifcgeom::Point_3{3, 0, 3},
    ifcgeom::Point_3{3, 3, 3}, ifcgeom::Point_3{0, 3, 3}};
std::vector<ifcgeom::Point_3> const vec_2{
    ifcgeom::Point_3{1, 1, 1}, ifcgeom::Point_3{4, 1, 1},
    ifcgeom::Point_3{4, 4, 1}, ifcgeom::Point_3{1, 4, 1},
    ifcgeom::Point_3{1, 1, 4}, ifcgeom::Point_3{4, 1, 4},
    ifcgeom::Point_3{4, 4, 4}, ifcgeom::Point_3{1, 4, 4}};

TEST_CASE("Boolean OP Nef_Polyhedron") {
  ifcgeom::Polyhedron_3 polyhedron_1, polyhedron_2;
  CGAL::convex_hull_3(vec_1.begin(), vec_1.end(), polyhedron_1);
  CGAL::convex_hull_3(vec_2.begin(), vec_2.end(), polyhedron_2);
  REQUIRE(polyhedron_1.size_of_vertices() > 0);

  ifcgeom::Nef_Polyhedron_3 nef_poly_1{polyhedron_1};
  ifcgeom::Nef_Polyhedron_3 nef_poly_2{polyhedron_2};
  CHECK(!nef_poly_1.is_empty());

  auto vol = CGAL::Polygon_mesh_processing::volume(polyhedron_1);
  CHECK(static_cast<unsigned>(vol) == 27);

  SUBCASE("UNION") {
    ifcgeom::Nef_Polyhedron_3 boolean_union{nef_poly_1 + nef_poly_2};
    check_boolean(boolean_union, 46);
  }
  SUBCASE("DIFFERENCE") {
    ifcgeom::Nef_Polyhedron_3 boolean_difference{nef_poly_1 - nef_poly_2};
    check_boolean(boolean_difference, 19);
  }
  SUBCASE("INTERSECTION") {
    ifcgeom::Nef_Polyhedron_3 boolean_intersection{nef_poly_1 * nef_poly_2};
    check_boolean(boolean_intersection, 8);
  }
}

TEST_CASE("Boolean OP SurfaceMesh") {
  ifcgeom::Mesh mesh_1, mesh_2;
  CGAL::convex_hull_3(vec_1.begin(), vec_1.end(), mesh_1);
  CGAL::convex_hull_3(vec_2.begin(), vec_2.end(), mesh_2);
  REQUIRE(CGAL::num_vertices(mesh_1) > 0);

  ifcgeom::Mesh result;
  SUBCASE("UNION") {
    CGAL::Polygon_mesh_processing::corefine_and_compute_union(mesh_1, mesh_2,
                                                              result);
    check_boolean(result, 46);
  }
  SUBCASE("DIFFERENCE") {
    CGAL::Polygon_mesh_processing::corefine_and_compute_difference(
        mesh_1, mesh_2, result);
    check_boolean(result, 19);
  }
  SUBCASE("INTERSECTION") {
    CGAL::Polygon_mesh_processing::corefine_and_compute_intersection(
        mesh_1, mesh_2, result);
    check_boolean(result, 8);
  }
}
