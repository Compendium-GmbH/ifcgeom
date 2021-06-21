#pragma once

#include <vector>

#include "IFC2X3/IfcGeometricCurveSet.h"
#include "IFC2X3/IfcGeometricSet.h"
#include "IFC2X3/IfcGeometricSetSelect.h"

#include "ifcgeom/core/types.h"

namespace ifcgeom {

std::vector<Point_3> geometric_set(IFC2X3::IfcGeometricSet const* set);
std::vector<Point_3> geometric_crv_set(IFC2X3::IfcGeometricCurveSet const* set);

std::vector<Point_3> geometric_set_handler(IFC2X3::IfcGeometricSet* set);

}  // namespace ifcgeom