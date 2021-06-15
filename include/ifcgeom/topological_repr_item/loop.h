#pragma once

#include "IFC2X3/IfcEdgeLoop.h"
#include "IFC2X3/IfcLoop.h"
#include "IFC2X3/IfcPolyLoop.h"
#include "IFC2X3/IfcVertexLoop.h"

#include "ifcgeom/core/context.h"
#include "ifcgeom/core/utilities.h"

namespace ifcgeom {

std::vector<Point_3> loop(IFC2X3::IfcLoop const* loop) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{loop->name()}, __func__);
  return vertices;
}

std::vector<Point_3> poly_loop(IFC2X3::IfcPolyLoop const* loop) {
  std::vector<Point_3> vertices;
  for (auto const pt : loop->Polygon_) {
    vertices.push_back(to_point_3(pt));
  }
  return vertices;
}

std::vector<Point_3> vertex_loop(IFC2X3::IfcPolyLoop const* loop) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{loop->name()}, __func__);
  return vertices;
}

std::vector<Point_3> edge_loop(IFC2X3::IfcPolyLoop const* loop) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{loop->name()}, __func__);
  return vertices;
}

std::vector<Point_3> loop_handler(IFC2X3::IfcLoop* item) {
  std::vector<Point_3> vertices{};
  utl::concat(vertices, match(item, poly_loop, vertex_loop, edge_loop, loop));
  return vertices;
}

}  // namespace ifcgeom