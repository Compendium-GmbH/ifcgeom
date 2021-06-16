#pragma once

#include <vector>

#include "utl/concat.h"
#include "utl/parser/cstr.h"

#include "IFC2X3/IfcPath.h"
#include "IFC2X3/IfcTopologicalRepresentationItem.h"

#include "ifcgeom/topological_repr_item/connected_face_set.h"
#include "ifcgeom/topological_repr_item/edge.h"
#include "ifcgeom/topological_repr_item/face.h"
#include "ifcgeom/topological_repr_item/face_bound.h"
#include "ifcgeom/topological_repr_item/loop.h"
#include "ifcgeom/topological_repr_item/vertex.h"

#include "ifcgeom/core/match.h"

namespace ifcgeom {

std::vector<Point_3> path(IFC2X3::IfcPath const* path) {
  std::vector<Point_3> vertices;
  render_err_log_.emplace_back(std::string{path->name()});
  return vertices;
}

std::vector<Point_3> topological_repr_item_handler(
    IFC2X3::IfcTopologicalRepresentationItem* item) {
  return match(item, connected_face_set_handler, edge_handler, face_handler,
               face_bound_handler, path, vertex_handler, loop_handler);
}

}  // namespace ifcgeom
