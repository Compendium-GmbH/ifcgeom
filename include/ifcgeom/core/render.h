#pragma once

#include <fstream>
#include <iostream>

#include "utl/concat.h"
#include "utl/parser/cstr.h"

#include "IFC2X3/IfcProductDefinitionShape.h"
#include "IFC2X3/IfcRepresentation.h"
#include "IFC2X3/IfcRepresentationItem.h"
#include "IFC2X3/IfcShapeRepresentation.h"

#include "ifcgeom/geometric_repr_item.h"
#include "ifcgeom/mapped_item.h"
#include "ifcgeom/styled_item.h"
#include "ifcgeom/topological_repr_item.h"

#include "ifcgeom/core/context.h"
#include "ifcgeom/core/match.h"
#include "ifcgeom/core/queries.h"
#include "ifcgeom/core/xform.h"

namespace ifcgeom {

inline std::vector<Point_3> gather_vertices(
    IFC2X3::IfcRepresentation const* repr) {
  auto vec = std::vector<Point_3>{};

  auto acc_vertices =
      [&](std::vector<IFC2X3::IfcRepresentationItem*> const& items) {
        for (auto const item : items) {
          utl::concat(vec, match(item, topological_repr_item_handler,
                                 geometric_repr_item_handler, mapped_item,
                                 styled_item));
        }
      };

  acc_vertices(repr->Items_);

  return vec;
}

inline std::vector<Point_3> gather_vertices(
    IFC2X3::IfcProductDefinitionShape const* pds) {
  auto vec = std::vector<Point_3>{};

  auto acc_vertices =
      [&](std::vector<IFC2X3::IfcRepresentationItem*> const& items) {
        for (auto const item : items) {
          utl::concat(vec, match(item, topological_repr_item_handler,
                                 geometric_repr_item_handler, mapped_item,
                                 styled_item));
        }
      };

  for (auto const r : pds->Representations_) {
    acc_vertices(r->Items_);
  }

  return vec;
}

inline std::vector<Point_3> gather_product_vertices(
    context& ctx, IFC2X3::IfcProduct const* p) {
  auto vec = std::vector<Point_3>{};
  if (!p->Representation_.has_value()) {
    return vec;
  }

  utl::concat(vec, gather_vertices(
                       dynamic_cast<IFC2X3::IfcProductDefinitionShape const*>(
                           p->Representation_.value())));

  auto shapes = repr_by_guid(ctx.element_part_map_, p->GlobalId_);
  for (auto const shape : shapes) {
    auto pds = dynamic_cast<IFC2X3::IfcProductDefinitionShape const*>(shape);
    utl::concat(vec, gather_vertices(pds));
  }

  auto const local_plcmt = reinterpret_cast<IFC2X3::IfcLocalPlacement const*>(
      p->ObjectPlacement_.value());
  vec = ifcgeom::cartesian_transformation(local_plcmt, vec);

  std::sort(begin(vec), end(vec));

  return vec;
}

inline std::vector<Point_3> gather_product_vertices(context& ctx,
                                                    char const* c) {
  auto p = get_entity_by_guid<IFC2X3::IfcProduct>(ctx.model_, c);
  if (p.has_value()) {
    return gather_product_vertices(ctx, p.value());
  }
  return std::vector<Point_3>{};
}

}  // namespace ifcgeom
