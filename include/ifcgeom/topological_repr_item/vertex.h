#pragma once

#include <vector>

#include "utl/concat.h"
#include "utl/parser/cstr.h"

#include "IFC2X3/IfcVertex.h"
#include "IFC2X3/IfcVertexPoint.h"

#include "ifcgeom/core/match.h"

namespace ifcgeom {

std::vector<Point_3> vertex(IFC2X3::IfcVertex const* vertex) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{vertex->name()}, __func__);
  return vertices;
}
std::vector<Point_3> vertex_point(IFC2X3::IfcVertexPoint const* vertex) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{vertex->name()}, __func__);
  return vertices;
}

std::vector<Point_3> vertex_handler(IFC2X3::IfcVertex* item) {
  std::vector<Point_3> vertices{};
  utl::concat(vertices, match(item, vertex_point, vertex));
  return vertices;
}

}  // namespace ifcgeom