#pragma once

#include <vector>

#include "utl/concat.h"
#include "utl/parser/cstr.h"

#include "IFC2X3/IfcGeometricCurveSet.h"
#include "IFC2X3/IfcGeometricSet.h"

namespace ifcgeom {

std::vector<Point_3> geometric_set(IFC2X3::IfcGeometricSet const* set) {
  std::vector<Point_3> vertices;
  render_err_log_.emplace_back(std::string{set->name()});
  return vertices;
}
std::vector<Point_3> geometric_crv_set(
    IFC2X3::IfcGeometricCurveSet const* set) {
  std::vector<Point_3> vertices;
  render_err_log_.emplace_back(std::string{set->name()});
  return vertices;
}

std::vector<Point_3> geometric_set_handler(IFC2X3::IfcGeometricSet* set) {
  return match(set, geometric_crv_set, geometric_set);
}

}  // namespace ifcgeom