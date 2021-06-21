#pragma once

#include <vector>

#include "IFC2X3/IfcStyledItem.h"

#include "ifcgeom/core/types.h"

namespace ifcgeom {

std::vector<Point_3> styled_item(IFC2X3::IfcStyledItem const* item);

}  // namespace ifcgeom
