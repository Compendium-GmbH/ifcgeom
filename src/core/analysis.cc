#include "ifcgeom/core/analysis.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include "IFC2X3/IfcProduct.h"
#include "IFC2X3/IfcProductRepresentation.h"
#include "IFC2X3/IfcRepresentation.h"
#include "IFC2X3/IfcRepresentationItem.h"

#include "ifcgeom/core/context.h"
#include "ifcgeom/core/filters.h"
#include "ifcgeom/core/utilities.h"

namespace ifcgeom {

void iterate_repr(IFC2X3::IfcProductRepresentation const* prod) {
  for (auto const repr : prod->Representations_) {
    render_err_log.emplace_back(repr->name());
    for (auto const item : repr->Items_) {
      render_err_log.emplace_back(item->name());
    }
  }
}

void list_geometry_types(std::string const& path) {
  auto n_products = 0;
  auto ctx = ifcgeom::context{path};
  auto products = ifcgeom::filter_entities<IFC2X3::IfcProduct>(ctx.model_);
  for (auto const p : products) {
    if (!p->Representation_.has_value()) {
      continue;
    }
    ++n_products;
    iterate_repr(p->Representation_.value());
    auto shapes = ifcgeom::repr_by_guid(ctx.element_part_map_, p->GlobalId_);
    for (auto const repr : shapes) {
      iterate_repr(repr);
    }
  }
  std::cout << "n_products = " << n_products << "\n";
}

}  // namespace ifcgeom
