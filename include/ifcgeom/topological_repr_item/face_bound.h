#pragma once

#include <vector>

#include "utl/concat.h"
#include "utl/parser/cstr.h"

#include "IFC2X3/IfcFaceBound.h"
#include "IFC2X3/IfcFaceOuterBound.h"

#include "ifcgeom/core/match.h"

namespace ifcgeom {

std::vector<Point_3> face_bound(IFC2X3::IfcFaceBound const* face) {
  std::vector<Point_3> vertices;
  render_err_log_.emplace_back(std::string{face->name()});
  return vertices;
}
std::vector<Point_3> face_outer_bound(IFC2X3::IfcFaceOuterBound const* face) {
  std::vector<Point_3> vertices;
  render_err_log_.emplace_back(std::string{face->name()});
  return vertices;
}

std::vector<Point_3> face_bound_handler(IFC2X3::IfcFaceBound* item) {
  return match(item, face_outer_bound, face_bound);
}

}  // namespace ifcgeom