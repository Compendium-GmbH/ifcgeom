#pragma once

#include "IFC2X3/IfcBoxedHalfSpace.h"
#include "IFC2X3/IfcHalfSpaceSolid.h"
#include "IFC2X3/IfcPolygonalBoundedHalfSpace.h"

#include "ifcgeom/core/types.h"

namespace ifcgeom {

std::vector<Point_3> half_space_solid(IFC2X3::IfcHalfSpaceSolid const* solid);
std::vector<Point_3> boxed_half_space(IFC2X3::IfcBoxedHalfSpace const* solid);
std::vector<Point_3> poly_bounded_half_space(
    IFC2X3::IfcPolygonalBoundedHalfSpace const* solid);

std::vector<Point_3> half_space_solid_handler(IFC2X3::IfcHalfSpaceSolid* item);

}  // namespace ifcgeom
