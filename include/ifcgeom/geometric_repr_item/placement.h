#pragma once

#include <vector>

#include "IFC2X3/IfcAxis1Placement.h"
#include "IFC2X3/IfcAxis2Placement2D.h"
#include "IFC2X3/IfcAxis2Placement3D.h"

#include "ifcgeom/core/types.h"

namespace ifcgeom {

std::vector<Point_3> axis_1_placement(IFC2X3::IfcAxis1Placement const* a1p);
std::vector<Point_3> axis_2_placement_2d(
    IFC2X3::IfcAxis2Placement2D const* a2p);
std::vector<Point_3> axis_2_placement_3d(
    IFC2X3::IfcAxis2Placement3D const* a2p);

std::vector<Point_3> placement_handler(IFC2X3::IfcPlacement* item);

}  // namespace ifcgeom
