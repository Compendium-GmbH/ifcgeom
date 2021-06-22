#pragma once

#include <vector>

#include "IFC2X3/IfcFaceBound.h"
#include "IFC2X3/IfcFaceOuterBound.h"

#include "ifcgeom/core/types.h"

namespace ifcgeom {

std::vector<Point_3> face_bound(IFC2X3::IfcFaceBound const* bound);
std::vector<Point_3> face_outer_bound(IFC2X3::IfcFaceOuterBound const* bound);

std::vector<Point_3> face_bound_handler(IFC2X3::IfcFaceBound* bound);

}  // namespace ifcgeom
