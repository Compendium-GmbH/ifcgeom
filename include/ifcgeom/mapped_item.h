#pragma once

#include <vector>

#include "utl/concat.h"
#include "utl/parser/cstr.h"

#include "IFC2X3/IfcMappedItem.h"
#include "IFC2X3/IfcRepresentation.h"

#include "ifcgeom/geometric_repr_item.h"
#include "ifcgeom/styled_item.h"
#include "ifcgeom/topological_repr_item.h"

#include "ifcgeom/core/match.h"

namespace ifcgeom {

std::vector<Point_3> mapped_item(IFC2X3::IfcMappedItem const* item) {
  std::vector<Point_3> vertices;
  for (auto const i : item->MappingSource_->MappedRepresentation_->Items_) {
    utl::concat(vertices,
                match(i, topological_repr_item_handler,
                      geometric_repr_item_handler, mapped_item, styled_item));
  }
  return vertices;
}

}  // namespace ifcgeom
