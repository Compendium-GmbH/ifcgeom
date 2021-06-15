#include <vector>

#include "IFC2X3/IfcProduct.h"

#include "CGAL/Polygon_mesh_processing/measure.h"
#include "CGAL/convex_hull_3.h"

#include "ifcgeom/core/analysis.h"
#include "ifcgeom/core/context.h"
#include "ifcgeom/core/render.h"

#include "ifcgeom/tools/filters.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <step_file> <GUID>";
    return 1;
  }

  auto const start = std::chrono::high_resolution_clock::now();
  auto const paths = ifcgeom::get_ifc_paths(argv[1]);

  if (!paths.empty()) {
    for (int i = 0; i < paths.size(); ++i) {
      std::cout << "Loading context [" << i + 1 << "/" << paths.size()
                << "] : " << paths.at(i).c_str() << std::endl;
      ifcgeom::context ctx{paths.at(i).string()};
      auto e = ifcgeom::filter_entities<IFC2X3::IfcProduct>(ctx.model_);
      for (auto const p : e) {
        auto const geo = ifcgeom::gather_product_vertices(ctx, p);
      }
    }
  } else {
    std::cout << "No Paths to valid IFC Models Provided !" << std::endl;
  }

  std::cout << std::endl;
  ifcgeom::print(ifcgeom::render_err_log_);

  std::cout << std::endl;
  auto const end = std::chrono::high_resolution_clock::now();
  auto const time_span =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::chrono::duration<double, std::milli> ms_double = end - start;
  std::cout << "Mapped Geometries in " << ms_double.count() / 1000
            << " Seconds !" << std::endl;
}