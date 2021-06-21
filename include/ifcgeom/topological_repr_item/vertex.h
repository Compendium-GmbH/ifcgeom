#pragma once

#include <vector>

#include "IFC2X3/IfcVertex.h"
#include "IFC2X3/IfcVertexPoint.h"

#include "ifcgeom/core/types.h"

namespace ifcgeom {

std::vector<Point_3> vertex(IFC2X3::IfcVertex const* vertex);
std::vector<Point_3> vertex_point(IFC2X3::IfcVertexPoint const* vertex);

std::vector<Point_3> vertex_handler(IFC2X3::IfcVertex* item);

}  // namespace ifcgeom