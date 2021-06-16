#pragma once

#include <fstream>
#include <iostream>

#include "utl/concat.h"
#include "utl/parser/cstr.h"

#include "IFC2X3/IfcRepresentationItem.h"

#include "ifcgeom/geometric_repr_item.h"
#include "ifcgeom/mapped_item.h"
#include "ifcgeom/styled_item.h"
#include "ifcgeom/topological_repr_item.h"

#include "ifcgeom/core/match.h"

#include "ifcgeom/tools/queries.h"

namespace ifcgeom {

std::vector<Point_3> gather_product_vertices(context& ctx,
                                             IFC2X3::IfcProduct const* p) {
  auto vec = std::vector<Point_3>{};
  if (!p->Representation_.has_value()) {
    return vec;
  }

  auto gather_vertices =
      [&](std::vector<IFC2X3::IfcRepresentationItem*> const& items) {
        for (auto const item : items) {
          utl::concat(vec, match(item, topological_repr_item_handler,
                                 geometric_repr_item_handler, mapped_item,
                                 styled_item));
        }
      };

  for (auto const repr : p->Representation_.value()->Representations_) {
    gather_vertices(repr->Items_);
  }

  auto shapes = repr_by_guid(ctx.element_part_map_, p->GlobalId_);
  for (auto const repr : shapes) {
    for (auto const repr : repr->Representations_) {
      gather_vertices(repr->Items_);
    }
  }
  return vec;
}
std::vector<Point_3> gather_product_vertices(context& ctx, char const* c) {
  auto p = get_entity_by_guid<IFC2X3::IfcProduct>(ctx.model_, c);
  if (p.has_value()) {
    return gather_product_vertices(ctx, p.value());
  }
  return std::vector<Point_3>{};
}

}  // namespace ifcgeom
