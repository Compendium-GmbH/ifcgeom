#include "doctest/doctest.h"

#include <iterator>
#include <vector>

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

TEST_CASE("Boolean Test") {
  std::vector<ifcgeom::Point_3> vec{
      ifcgeom::Point_3{0, 0, 0}, ifcgeom::Point_3{3, 0, 0},
      ifcgeom::Point_3{3, 3, 0}, ifcgeom::Point_3{0, 3, 0},
      ifcgeom::Point_3{0, 0, 3}, ifcgeom::Point_3{3, 0, 3},
      ifcgeom::Point_3{3, 3, 3}, ifcgeom::Point_3{0, 3, 3}};

  ifcgeom::Polyhedron_3 polyhedron;
  CGAL::convex_hull_3(vec.begin(), vec.end(), polyhedron);
  REQUIRE(polyhedron.size_of_vertices() > 0);

  ifcgeom::Nef_Polyhedron_3 nef_polyhedron{polyhedron};
  //  ifcgeom::Nef_polyhedron nef_polyhedron{vec.begin(), vec.end(), {}};
  CHECK(!nef_polyhedron.is_empty());

  ifcgeom::Xform_3 xform{CGAL::TRANSLATION, ifcgeom::Vector_3{1, 1, 1}};
  auto nef_poly_2 = ifcgeom::Nef_Polyhedron_3{nef_polyhedron};
  nef_poly_2.transform(xform);

  auto vol = CGAL::Polygon_mesh_processing::volume(polyhedron);
  CHECK(static_cast<unsigned>(vol) == 27);

  SUBCASE("UNION") {
    ifcgeom::Nef_Polyhedron_3 boolean_union{nef_polyhedron + nef_poly_2};
    check_boolean(boolean_union, 46);
  }
  SUBCASE("DIFFERENCE") {
    ifcgeom::Nef_Polyhedron_3 boolean_difference{nef_polyhedron - nef_poly_2};
    check_boolean(boolean_difference, 19);
  }
  SUBCASE("INTERSECTION") {
    ifcgeom::Nef_Polyhedron_3 boolean_intersection{nef_polyhedron * nef_poly_2};
    check_boolean(boolean_intersection, 8);
  }
}