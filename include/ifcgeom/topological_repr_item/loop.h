#pragma once

#include "IFC2X3/IfcEdgeLoop.h"
#include "IFC2X3/IfcLoop.h"
#include "IFC2X3/IfcPolyLoop.h"
#include "IFC2X3/IfcVertexLoop.h"

#include "ifcgeom/core/types.h"

namespace ifcgeom {

std::vector<Point_3> loop(IFC2X3::IfcLoop const* loop);
std::vector<Point_3> poly_loop(IFC2X3::IfcPolyLoop const* loop);
std::vector<Point_3> vertex_loop(IFC2X3::IfcPolyLoop const* loop);
std::vector<Point_3> edge_loop(IFC2X3::IfcPolyLoop const* loop);

std::vector<Point_3> loop_handler(IFC2X3::IfcLoop* item);

}  // namespace ifcgeom
