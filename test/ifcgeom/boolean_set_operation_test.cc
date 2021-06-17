#include "doctest/doctest.h"

#include <iterator>
#include <vector>

#include <CGAL/Exact_integer.h>
#include <CGAL/Nef_polyhedron_3.h>
#include "CGAL/Polygon_mesh_processing/measure.h"
#include "CGAL/convex_hull_3.h"

#include "ifcgeom/core/context.h"

using Nef_polyhedron = CGAL::Nef_polyhedron_3<ifcgeom::K>;

TEST_CASE("Boolean Test") {
  std::vector<ifcgeom::Point_3> vec{
      ifcgeom::Point_3{0, 0, 0}, ifcgeom::Point_3{3, 0, 0},
      ifcgeom::Point_3{3, 3, 0}, ifcgeom::Point_3{0, 3, 0},
      ifcgeom::Point_3{0, 0, 3}, ifcgeom::Point_3{3, 0, 3},
      ifcgeom::Point_3{3, 3, 3}, ifcgeom::Point_3{0, 3, 3}};

  ifcgeom::Polyhedron_3 polyhedron;
  CGAL::convex_hull_3(vec.begin(), vec.end(), polyhedron);
  REQUIRE(polyhedron.size_of_vertices() > 0);

  Nef_polyhedron nef_polyhedron{polyhedron};
  CHECK(!nef_polyhedron.is_empty());

  ifcgeom::Xform_3 xform{CGAL::TRANSLATION, ifcgeom::Vector_3{1, 1, 1}};
  auto nef_poly_2 = Nef_polyhedron{nef_polyhedron};
  nef_poly_2.transform(xform);

  auto vol = CGAL::Polygon_mesh_processing::volume(polyhedron);
  CHECK(vol == static_cast<double>(27));

  SUBCASE("UNION") {
    Nef_polyhedron boolean_union{nef_polyhedron + nef_poly_2};
    REQUIRE(!boolean_union.is_empty());

    ifcgeom::Polyhedron_3 union_polyhedron;
    boolean_union.convert_to_Polyhedron(union_polyhedron);
    auto union_vol = CGAL::Polygon_mesh_processing::volume(union_polyhedron);
    CHECK(static_cast<unsigned>(union_vol) == 46);
  }
  SUBCASE("DIFFERENCE") {
    Nef_polyhedron boolean_difference{nef_polyhedron - nef_poly_2};
    REQUIRE(!boolean_difference.is_empty());

    ifcgeom::Polyhedron_3 difference_polyhedron;
    boolean_difference.convert_to_Polyhedron(difference_polyhedron);
    auto difference_vol =
        CGAL::Polygon_mesh_processing::volume(difference_polyhedron);
    CHECK(static_cast<unsigned>(difference_vol) == 19);
  }
  SUBCASE("INTERSECTION") {
    Nef_polyhedron boolean_intersection{nef_polyhedron * nef_poly_2};
    REQUIRE(!boolean_intersection.is_empty());

    ifcgeom::Polyhedron_3 intersection_polyhedron;
    boolean_intersection.convert_to_Polyhedron(intersection_polyhedron);
    auto intersection_vol =
        CGAL::Polygon_mesh_processing::volume(intersection_polyhedron);
    CHECK(static_cast<unsigned>(intersection_vol) == 8);
  }
}