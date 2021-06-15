#pragma once

#include <vector>

#include "utl/concat.h"
#include "utl/parser/cstr.h"

#include "IFC2X3/IfcFace.h"
#include "IFC2X3/IfcFaceSurface.h"

#include "ifcgeom/core/match.h"

namespace ifcgeom {

std::vector<Point_3> face(IFC2X3::IfcFace const* face) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{face->name()}, __func__);
  return vertices;
}
std::vector<Point_3> face_surface(IFC2X3::IfcFaceSurface const* face) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{face->name()}, __func__);
  return vertices;
}

std::vector<Point_3> face_handler(IFC2X3::IfcFace* item) {
  std::vector<Point_3> vertices{};
  utl::concat(vertices, match(item, face_surface, face));
  return vertices;
}

}  // namespace ifcgeom