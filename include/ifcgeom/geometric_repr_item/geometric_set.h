#pragma once

#include <vector>

#include "utl/concat.h"
#include "utl/parser/cstr.h"

#include "IFC2X3/IfcGeometricCurveSet.h"
#include "IFC2X3/IfcGeometricSet.h"

namespace ifcgeom {

std::vector<Point_3> geometric_set(IFC2X3::IfcGeometricSet const* set) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{set->name()}, __func__);
  return vertices;
}
std::vector<Point_3> geometric_crv_set(
    IFC2X3::IfcGeometricCurveSet const* set) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{set->name()}, __func__);
  return vertices;
}

std::vector<Point_3> geometric_set_handler(IFC2X3::IfcGeometricSet* set) {
  std::vector<Point_3> vertices{};
  utl::concat(vertices, match(set, geometric_crv_set, geometric_set));
  return vertices;
}

}  // namespace ifcgeom