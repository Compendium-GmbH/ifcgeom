#pragma once

#include <vector>

#include "utl/concat.h"
#include "utl/parser/cstr.h"

#include "IFC2X3/IfcEdge.h"
#include "IFC2X3/IfcEdgeCurve.h"
#include "IFC2X3/IfcOrientedEdge.h"
#include "IFC2X3/IfcSubedge.h"

#include "ifcgeom/core/match.h"

namespace ifcgeom {

std::vector<Point_3> edge(IFC2X3::IfcEdge const* edge) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{edge->name()}, __func__);
  return vertices;
}
std::vector<Point_3> oriented_edge(IFC2X3::IfcOrientedEdge const* edge) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{edge->name()}, __func__);
  return vertices;
}
std::vector<Point_3> edge_curve(IFC2X3::IfcEdgeCurve const* edge) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{edge->name()}, __func__);
  return vertices;
}
std::vector<Point_3> sub_edge(IFC2X3::IfcSubedge const* edge) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{edge->name()}, __func__);
  return vertices;
}

std::vector<Point_3> edge_handler(IFC2X3::IfcEdge* item) {
  std::vector<Point_3> vertices{};
  utl::concat(vertices, match(item, oriented_edge, edge_curve, sub_edge, edge));
  return vertices;
}

}  // namespace ifcgeom