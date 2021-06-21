#include "ifcgeom/geometric_repr_item/point.h"

#include <vector>

#include "IFC2X3/IfcCartesianPoint.h"
#include "IFC2X3/IfcPointOnCurve.h"
#include "IFC2X3/IfcPointOnSurface.h"

#include "ifcgeom/core/context.h"
#include "ifcgeom/core/match.h"

namespace ifcgeom {

std::vector<Point_3> cartesian_point(IFC2X3::IfcCartesianPoint const* pt) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{pt->name()});
  return vertices;
}
std::vector<Point_3> point_on_crv(IFC2X3::IfcPointOnCurve const* pt) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{pt->name()});
  return vertices;
}
std::vector<Point_3> point_on_srf(IFC2X3::IfcPointOnSurface const* pt) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{pt->name()});
  return vertices;
}

std::vector<Point_3> point_handler(IFC2X3::IfcPoint* item) {
  return match(item, cartesian_point, point_on_crv, point_on_srf);
}

}  // namespace ifcgeom