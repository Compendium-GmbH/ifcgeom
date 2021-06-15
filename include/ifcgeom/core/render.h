#pragma once

#include <fstream>
#include <iostream>

#include "utl/concat.h"
#include "utl/parser/cstr.h"

#include "ifcgeom/geometric_repr_item.h"
#include "ifcgeom/mapped_item.h"
#include "ifcgeom/styled_item.h"
#include "ifcgeom/topological_repr_item.h"

#include "ifcgeom/core/analysis.h"
#include "ifcgeom/core/match.h"

#include "ifcgeom/tools/queries.h"

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

  auto shapes = repr_by_guid(ctx.element_part_map_, p->GlobalId_);
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
}std::vector<Point_3> gather_product_vertices(context& ctx,
                                             char const* c) {
  auto p = get_entity_by_guid<IFC2X3::IfcProduct>(ctx.model_, c);
  if(p.has_value()){
    return gather_product_vertices(ctx, p.value());
  }
  return std::vector<Point_3 >{};
}

}  // namespace ifcgeom
