#pragma once

#include <vector>

#include "IFC2X3/IfcClosedShell.h"
#include "IFC2X3/IfcConnectedFaceSet.h"
#include "IFC2X3/IfcOpenShell.h"

#include "ifcgeom/core/types.h"

namespace ifcgeom {

std::vector<Point_3> connected_face_set(IFC2X3::IfcConnectedFaceSet const* set);
std::vector<Point_3> closed_shell(IFC2X3::IfcClosedShell const* shell);
std::vector<Point_3> open_shell(IFC2X3::IfcOpenShell const* shell);

std::vector<Point_3> connected_face_set_handler(
    IFC2X3::IfcConnectedFaceSet* item);

}  // namespace ifcgeom