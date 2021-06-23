#pragma once

#include <vector>

#include "IFC2X3/IfcBooleanClippingResult.h"
#include "IFC2X3/IfcBooleanOperand.h"
#include "IFC2X3/IfcBooleanResult.h"
#include "IFC2X3/IfcCsgPrimitive3D.h"

#include "ifcgeom/core/types.h"

namespace ifcgeom {

std::vector<Point_3> boolean_result(IFC2X3::IfcBooleanResult const* res);
std::vector<Point_3> boolean_clipping_result(
    IFC2X3::IfcBooleanClippingResult const* res);

std::vector<Point_3> boolean_result_handler(IFC2X3::IfcBooleanResult* item);

}  // namespace ifcgeom