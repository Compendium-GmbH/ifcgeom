#include "ifcgeom/topological_repr_item/face.h"

#include <vector>

#include "utl/concat.h"
#include "utl/parser/cstr.h"

#include "IFC2X3/IfcFace.h"
#include "IFC2X3/IfcFaceSurface.h"

#include "ifcgeom/core/context.h"
#include "ifcgeom/core/match.h"

#include "ifcgeom/topological_repr_item/face_bound.h"

namespace ifcgeom {

std::vector<Point_3> face(IFC2X3::IfcFace const* face) {
  std::vector<Point_3> vertices;
  for (auto const bound : face->Bounds_) {
    utl::concat(vertices, face_bound_handler(bound));
  }
  return vertices;
}
std::vector<Point_3> face_surface(IFC2X3::IfcFaceSurface const* face) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{face->name()});
  return vertices;
}

std::vector<Point_3> face_handler(IFC2X3::IfcFace* item) {
  return match(item, face_surface, face);
}

}  // namespace ifcgeom