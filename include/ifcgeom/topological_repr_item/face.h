#pragma once

#include <vector>

#include "IFC2X3/IfcFace.h"
#include "IFC2X3/IfcFaceSurface.h"

#include "ifcgeom/core/types.h"

namespace ifcgeom {

std::vector<Point_3> face(IFC2X3::IfcFace const* face);
std::vector<Point_3> face_surface(IFC2X3::IfcFaceSurface const* face);

std::vector<Point_3> face_handler(IFC2X3::IfcFace* item);

}  // namespace ifcgeom