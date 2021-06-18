#pragma once

#include <vector>

#include "utl/concat.h"
#include "utl/parser/cstr.h"

#include "IFC2X3/IfcBooleanClippingResult.h"
#include "IFC2X3/IfcBooleanOperand.h"
#include "IFC2X3/IfcBooleanResult.h"
#include "IFC2X3/IfcCsgPrimitive3D.h"

#include "CGAL/convex_hull_3.h"

#include "ifcgeom/core/match.h"

#include "ifcgeom/geometric_repr_item/half_space_solid.h"
#include "ifcgeom/geometric_repr_item/solid_model.h"

namespace ifcgeom {

std::vector<Point_3> boolean_result(IFC2X3::IfcBooleanResult const* res) {
  auto get_vertices = [](auto& variant) {
    return std::visit(
        [&](auto item) {
          return match(item, solid_model_handler, half_space_solid_handler,
                       boolean_result);
        },
        variant);
  };

  auto v_first = get_vertices(res->FirstOperand_.data_);
  auto v_second = get_vertices(res->SecondOperand_.data_);

  ifcgeom::Polyhedron_3 polyhedron;
  CGAL::convex_hull_3(v_first.begin(), v_first.end(), polyhedron);

  switch (res->Operator_) {
    case IFC2X3::IfcBooleanOperator::IFC2X3_UNION: break;
    case IFC2X3::IfcBooleanOperator::IFC2X3_DIFFERENCE: break;
    case IFC2X3::IfcBooleanOperator::IFC2X3_INTERSECTION: break;
  }
  return v_first;
}
std::vector<Point_3> boolean_clipping_result(
    IFC2X3::IfcBooleanClippingResult const* res) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{res->name()});
  return vertices;
}

std::vector<Point_3> boolean_result_handler(IFC2X3::IfcBooleanResult* item) {
  std::vector<Point_3> vertices{};
  utl::concat(vertices, match(item, boolean_clipping_result, boolean_result));
  return vertices;
}

}  // namespace ifcgeom