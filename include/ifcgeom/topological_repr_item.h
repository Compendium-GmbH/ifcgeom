#pragma once

#include <vector>

#include "IFC2X3/IfcPath.h"
#include "IFC2X3/IfcTopologicalRepresentationItem.h"

#include "ifcgeom/core/types.h"

namespace ifcgeom {

std::vector<Point_3> path(IFC2X3::IfcPath const* path);

std::vector<Point_3> topological_repr_item_handler(
    IFC2X3::IfcTopologicalRepresentationItem* item);

}  // namespace ifcgeom
