#include <iostream>

#include "IFC2X3/IfcProduct.h"
#include "IFC2X3/parser.h"

#include "ifcgeom/core/context.h"
#include "ifcgeom/core/filters.h"
#include "ifcgeom/core/geom_hash.h"
#include "ifcgeom/core/render.h"
#include "ifcgeom/core/types.h"

void print_vertices(std::vector<ifcgeom::Point_3> vertices) {
  for (auto const v : vertices) {
    std::cout << v << "\n";
  }
}

int main(int argc, char** argv) {
  if (argc != 3) {
    std::cout << "Usage: " << argv[0] << " <step_file 1> <step_file 2>";
    return 1;
  }

  auto path = argv[1];
  auto ctx = ifcgeom::context{path};

  std::cout << "Model loaded\n";

  auto map = std::unordered_map<double, std::string>{};
  auto collision_count = 0U;
  auto geometry_count = 0U;

  for (auto const p :
       ifcgeom::filter_entities<IFC2X3::IfcProduct>(ctx.model_)) {
    if (!p->Representation_.has_value()) {
      continue;
    }

    ++geometry_count;

    auto vertices = ifcgeom::gather_product_vertices(ctx, p);
    auto hash = ifcgeom::geom_hash(vertices);

    if (map.find(hash) == map.end()) {
      map.insert({hash, p->GlobalId_});
    } else {
      ++collision_count;
      auto const p1 = ifcgeom::get_entity_by_guid<IFC2X3::IfcProduct>(
          ctx.model_, map.at(hash));
      std::cout << p1.value()->GlobalId_ << "\n";
      auto const v = ifcgeom::gather_product_vertices(ctx, p1.value());
      print_vertices(v);
      ifcgeom::geom_hash<true>(v);

      std::cout << "\n\n";

      std::cout << p->GlobalId_ << "\n";
      print_vertices(vertices);
      ifcgeom::geom_hash<true>(v);

      if (collision_count == 3) {
        break;
      }

      std::cout << p->Representation_.value()
                       ->Representations_.at(0)
                       ->RepresentationType_.value()
                << "\n";
    }
  }

  std::cout << "geometry_count: " << geometry_count << "\n";
  std::cout << "collision_count: " << collision_count << "\n";
}