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
  add_to_map(render_err_log_, std::string{solid->name()}, __func__);
  return vertices;
}
std::vector<Point_3> boxed_half_space(IFC2X3::IfcBoxedHalfSpace const* solid) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{solid->name()}, __func__);
  return vertices;
}
std::vector<Point_3> poly_bounded_half_space(
    IFC2X3::IfcPolygonalBoundedHalfSpace const* solid) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{solid->name()}, __func__);
  return vertices;
}

std::vector<Point_3> half_space_solid_handler(IFC2X3::IfcHalfSpaceSolid* item) {
  std::vector<Point_3> vertices{};
  utl::concat(vertices, match(item, boxed_half_space, poly_bounded_half_space,
                              half_space_solid));
  return vertices;
}

}  // namespace ifcgeom
