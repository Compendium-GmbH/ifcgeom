#pragma once

#include <vector>

#include "IFC2X3/IfcMappedItem.h"

#include "ifcgeom/core/types.h"

namespace ifcgeom {

std::vector<Point_3> mapped_item(IFC2X3::IfcMappedItem const* item);

}  // namespace ifcgeom
