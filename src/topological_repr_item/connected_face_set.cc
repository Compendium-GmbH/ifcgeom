#include "ifcgeom/topological_repr_item/connected_face_set.h"

#include <vector>

#include "utl/concat.h"
#include "utl/parser/cstr.h"

#include "IFC2X3/IfcClosedShell.h"
#include "IFC2X3/IfcConnectedFaceSet.h"
#include "IFC2X3/IfcOpenShell.h"

#include "ifcgeom/core/match.h"

#include "ifcgeom/topological_repr_item/face.h"

namespace ifcgeom {

std::vector<Point_3> connected_face_set(
    IFC2X3::IfcConnectedFaceSet const* set) {
  std::vector<Point_3> vertices;
  for (auto const face : set->CfsFaces_) {
    utl::concat(vertices, face_handler(face));
  }
  return vertices;
}
std::vector<Point_3> closed_shell(IFC2X3::IfcClosedShell const* shell) {
  std::vector<Point_3> vertices;
  for (auto const face : shell->CfsFaces_) {
    utl::concat(vertices, face_handler(face));
  }
  return vertices;
}
std::vector<Point_3> open_shell(IFC2X3::IfcOpenShell const* shell) {
  std::vector<Point_3> vertices;
  for (auto const face : shell->CfsFaces_) {
    utl::concat(vertices, face_handler(face));
  }
  return vertices;
}

std::vector<Point_3> connected_face_set_handler(
    IFC2X3::IfcConnectedFaceSet* item) {
  return match(item, closed_shell, open_shell, connected_face_set);
}

}  // namespace ifcgeom