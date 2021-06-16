#pragma once

#include "utl/concat.h"
#include "utl/parser/cstr.h"

#include "IFC2X3/IfcBoxedHalfSpace.h"
#include "IFC2X3/IfcHalfSpaceSolid.h"
#include "IFC2X3/IfcPolygonalBoundedHalfSpace.h"

#include "ifcgeom/core/match.h"

namespace ifcgeom {

std::vector<Point_3> half_space_solid(IFC2X3::IfcHalfSpaceSolid const* solid) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{solid->name()});
  return vertices;
}
std::vector<Point_3> boxed_half_space(IFC2X3::IfcBoxedHalfSpace const* solid) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{solid->name()});
  return vertices;
}
std::vector<Point_3> poly_bounded_half_space(
    IFC2X3::IfcPolygonalBoundedHalfSpace const* solid) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{solid->name()});
  return vertices;
}

std::vector<Point_3> half_space_solid_handler(IFC2X3::IfcHalfSpaceSolid* item) {
  return match(item, boxed_half_space, poly_bounded_half_space,
               half_space_solid);
}

}  // namespace ifcgeom
