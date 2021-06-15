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
  add_to_map(render_err_log_, std::string{face->name()}, __func__);
  return vertices;
}
std::vector<Point_3> face_outer_bound(IFC2X3::IfcFaceOuterBound const* face) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{face->name()}, __func__);
  return vertices;
}

std::vector<Point_3> face_bound_handler(IFC2X3::IfcFaceBound* item) {
  std::vector<Point_3> vertices{};
  utl::concat(vertices, match(item, face_outer_bound, face_bound));
  return vertices;
}

}  // namespace ifcgeom