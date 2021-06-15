#pragma once

#include <vector>

#include "utl/concat.h"
#include "utl/parser/cstr.h"

#include "IFC2X3/IfcClosedShell.h"
#include "IFC2X3/IfcConnectedFaceSet.h"
#include "IFC2X3/IfcOpenShell.h"

#include "ifcgeom/core/match.h"

namespace ifcgeom {

std::vector<Point_3> connected_face_set(
    IFC2X3::IfcConnectedFaceSet const* set) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{set->name()}, __func__);
  return vertices;
}
std::vector<Point_3> closed_shell(IFC2X3::IfcClosedShell const* shell) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{shell->name()}, __func__);
  return vertices;
}
std::vector<Point_3> open_shell(IFC2X3::IfcOpenShell const* shell) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{shell->name()}, __func__);
  return vertices;
}

std::vector<Point_3> connected_face_set_handler(
    IFC2X3::IfcConnectedFaceSet* item) {
  std::vector<Point_3> vertices{};
  utl::concat(vertices,
              match(item, closed_shell, open_shell, connected_face_set));
  return vertices;
}

}  // namespace ifcgeom