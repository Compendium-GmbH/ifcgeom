#include "ifcgeom/geometric_repr_item/boolean_result.h"

#include <vector>

#include "utl/concat.h"
#include "utl/parser/cstr.h"

#include "CGAL/convex_hull_3.h"

#include "IFC2X3/IfcBooleanClippingResult.h"
#include "IFC2X3/IfcBooleanResult.h"

#include "ifcgeom/geometric_repr_item/half_space_solid.h"
#include "ifcgeom/geometric_repr_item/solid_model.h"

#include "ifcgeom/core/context.h"
#include "ifcgeom/core/match.h"

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

  Polyhedron_3 polyhedron_first;
  CGAL::convex_hull_3(v_first.begin(), v_first.end(), polyhedron_first);
  Polyhedron_3 polyhedron_second;
  CGAL::convex_hull_3(v_second.begin(), v_second.end(), polyhedron_second);

  if (polyhedron_first.is_closed() && polyhedron_second.is_closed()) {
    Nef_Polyhedron_3 nef_polyhedron_first{polyhedron_first};
    Nef_Polyhedron_3 nef_polyhedron_second{polyhedron_second};

    Nef_Polyhedron_3 boolean_result;
    switch (res->Operator_) {
      case IFC2X3::IfcBooleanOperator::IFC2X3_UNION:
        boolean_result = nef_polyhedron_first + nef_polyhedron_second;
        break;
      case IFC2X3::IfcBooleanOperator::IFC2X3_DIFFERENCE:
        boolean_result = nef_polyhedron_first - nef_polyhedron_second;
        break;
      case IFC2X3::IfcBooleanOperator::IFC2X3_INTERSECTION:
        boolean_result = nef_polyhedron_first * nef_polyhedron_second;
        break;
    }
  }

  return std::vector<Point_3>{};
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