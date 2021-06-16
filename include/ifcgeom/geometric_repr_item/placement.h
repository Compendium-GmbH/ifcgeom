#pragma once

#include <vector>

#include "utl/concat.h"
#include "utl/parser/cstr.h"

#include "IFC2X3/IfcAxis1Placement.h"
#include "IFC2X3/IfcAxis2Placement2D.h"
#include "IFC2X3/IfcAxis2Placement3D.h"

#include "ifcgeom/core/analysis.h"
#include "ifcgeom/core/match.h"

namespace ifcgeom {

std::vector<Point_3> axis_1_placement(IFC2X3::IfcAxis1Placement const* a1p) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{a1p->name()});
  return vertices;
}
std::vector<Point_3> axis_2_placement_2d(
    IFC2X3::IfcAxis2Placement2D const* a2p) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{a2p->name()});
  return vertices;
}
std::vector<Point_3> axis_2_placement_3d(
    IFC2X3::IfcAxis2Placement3D const* a2p) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{a2p->name()});
  return vertices;
}

std::vector<Point_3> placement_handler(IFC2X3::IfcPlacement* item) {
  return match(item, axis_1_placement, axis_2_placement_2d,
               axis_2_placement_3d);
}

}  // namespace ifcgeom
