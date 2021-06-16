#pragma once

#include <vector>

#include "utl/concat.h"
#include "utl/parser/cstr.h"

#include "IFC2X3/IfcStyledItem.h"

#include "ifcgeom/core/match.h"

namespace ifcgeom {

std::vector<Point_3> styled_item(IFC2X3::IfcStyledItem const* item) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{item->name()});
  return vertices;
}

}  // namespace ifcgeom
