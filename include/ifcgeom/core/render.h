#pragma once

#include <fstream>
#include <iostream>

#include "ifctools/filters.h"
#include "ifctools/queries.h"

#include "utl/concat.h"
#include "utl/parser/cstr.h"

#include "ifcgeom/geometric_repr_item.h"
#include "ifcgeom/mapped_item.h"
#include "ifcgeom/styled_item.h"
#include "ifcgeom/topological_repr_item.h"

#include "ifcgeom/core/analysis.h"
#include "ifcgeom/core/match.h"

namespace ifcgeom {

std::vector<Point_3> gather_product_vertices(context& ctx,
                                             IFC2X3::IfcProduct const* p) {
  auto vec = std::vector<Point_3>{};
  if (!p->Representation_.has_value()) {
    return vec;
  }

  for (auto const repr : p->Representation_.value()->Representations_) {
    for (auto const item : repr->Items_) {
      utl::concat(vec, match(item, solid_model_handler, polyline));
    }
  }

  auto shapes = ifctools::repr_by_guid(ctx.element_part_map_, p->GlobalId_);
  for (auto const repr : shapes) {
    for (auto const& repr : repr->Representations_) {
      for (auto const& item : repr->Items_) {
        utl::concat(
            vec, match(item, topological_repr_item_handler,
                       geometric_repr_item_handler, mapped_item, styled_item));
      }
    }
  }
  return vec;
}

}  // namespace ifcgeom
