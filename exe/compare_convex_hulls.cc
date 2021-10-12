#include "CGAL/Polygon_mesh_processing/measure.h"
#include "CGAL/convex_hull_3.h"

#include "ifcgeom/core/context.h"
#include "ifcgeom/core/render.h"

int main(int argc, char** argv) {
  if (argc != 5) {
    std::cout << "Usage: " << argv[0]
              << " <step_file 1> <step_file 2> <GUID 1> <GUID 2>";
    return 1;
  }

  std::cout << std::endl;
  // -------------------------------------------------------------

  // MODEL 1 (EXRTRUDED GEOMETRY)
  std::cout << "Loading context 1 : " << argv[1] << std::endl;
  ifcgeom::context ctx_1{argv[1]};
  auto const points_m1 = ifcgeom::gather_product_vertices(ctx_1, argv[3]);
  ifcgeom::Polyhedron_3 poly_m1;
  CGAL::convex_hull_3(points_m1.begin(), points_m1.end(), poly_m1);
  std::cout << "Convex hull 1 vertices: " << poly_m1.size_of_vertices()
            << std::endl;
  auto const v1 = CGAL::Polygon_mesh_processing::volume(poly_m1);
  std::cout << "Convex hull 1 volume: " << v1 << std::endl;

  auto const c1 = CGAL::Polygon_mesh_processing::centroid(poly_m1);
  std::cout << "Convex hull 1 centroid: " << c1 << std::endl;

  std::cout << std::endl;
  // -------------------------------------------------------------

  // MODEL 2 (BREP)
  std::cout << "Loading context 2 : " << argv[2] << std::endl;
  ifcgeom::context ctx_2{argv[2]};
  auto const points_m2 = ifcgeom::gather_product_vertices(ctx_2, argv[4]);
  ifcgeom::Polyhedron_3 poly_m2;
  CGAL::convex_hull_3(points_m2.begin(), points_m2.end(), poly_m2);
  std::cout << "Convex hull 2 vertices: " << poly_m2.size_of_vertices()
            << std::endl;

  auto const v2 = CGAL::Polygon_mesh_processing::volume(poly_m2);
  std::cout << "Convex hull 2 volume: " << v2 << std::endl;

  auto const c2 = CGAL::Polygon_mesh_processing::centroid(poly_m2);
  std::cout << "Convex hull 2 centroid: " << c2 << std::endl;

  std::cout << std::endl;
  // -------------------------------------------------------------

  // COMPARE
  std::cout << "Volume Model 1: " << v1 << std::endl;
  std::cout << "Volume Model 2: " << v2 << std::endl;
  std::cout << "Variance: " << 100 - (v1 / v2) * 100 << " %" << std::endl;
}