#pragma once

#include <variant>
#include <vector>

#include "IFC2X3/IfcCompositeCurveSegment.h"

#include "ifcgeom/core/types.h"

namespace ifcgeom {

std::vector<Point_3> composite_crv_segment(
    IFC2X3::IfcCompositeCurveSegment const* crv);

}  // namespace ifcgeom