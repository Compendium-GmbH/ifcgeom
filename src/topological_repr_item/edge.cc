#include "ifcgeom/topological_repr_item/edge.h"

#include <vector>

#include "IFC2X3/IfcEdge.h"
#include "IFC2X3/IfcEdgeCurve.h"
#include "IFC2X3/IfcOrientedEdge.h"
#include "IFC2X3/IfcSubedge.h"

#include "ifcgeom/core/context.h"
#include "ifcgeom/core/match.h"

namespace ifcgeom {

std::vector<Point_3> edge(IFC2X3::IfcEdge const* edge) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{edge->name()});
  return vertices;
}
std::vector<Point_3> oriented_edge(IFC2X3::IfcOrientedEdge const* edge) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{edge->name()});
  return vertices;
}
std::vector<Point_3> edge_curve(IFC2X3::IfcEdgeCurve const* edge) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{edge->name()});
  return vertices;
}
std::vector<Point_3> sub_edge(IFC2X3::IfcSubedge const* edge) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{edge->name()});
  return vertices;
}

std::vector<Point_3> edge_handler(IFC2X3::IfcEdge* item) {
  return match(item, oriented_edge, edge_curve, sub_edge, edge);
}

}  // namespace ifcgeom