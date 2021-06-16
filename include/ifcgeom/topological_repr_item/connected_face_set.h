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
  render_err_log.emplace_back(std::string{set->name()});
  return vertices;
}
std::vector<Point_3> closed_shell(IFC2X3::IfcClosedShell const* shell) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{shell->name()});
  return vertices;
}
std::vector<Point_3> open_shell(IFC2X3::IfcOpenShell const* shell) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{shell->name()});
  return vertices;
}

std::vector<Point_3> connected_face_set_handler(
    IFC2X3::IfcConnectedFaceSet* item) {
  return match(item, closed_shell, open_shell, connected_face_set);
}

}  // namespace ifcgeom