#pragma once

#include <vector>

#include "utl/concat.h"
#include "utl/parser/cstr.h"

#include "IFC2X3/IfcStyledItem.h"

#include "ifcgeom/core/match.h"

namespace ifcgeom {

std::vector<Point_3> styled_item(IFC2X3::IfcStyledItem const* item) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{item->name()}, __func__);
  return vertices;
}

}  // namespace ifcgeom
