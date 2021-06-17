#pragma once

#include <vector>

#include "utl/concat.h"
#include "utl/parser/cstr.h"

#include "IFC2X3/IfcFaceBound.h"
#include "IFC2X3/IfcFaceOuterBound.h"

#include "ifcgeom/core/match.h"

#include "ifcgeom/topological_repr_item/loop.h"

namespace ifcgeom {

std::vector<Point_3> face_bound(IFC2X3::IfcFaceBound const* bound) {
  return loop_handler(bound->Bound_);
}
std::vector<Point_3> face_outer_bound(IFC2X3::IfcFaceOuterBound const* bound) {
  return loop_handler(bound->Bound_);
}

std::vector<Point_3> face_bound_handler(IFC2X3::IfcFaceBound* bound) {
  return match(bound, face_outer_bound, face_bound);
}

}  // namespace ifcgeom