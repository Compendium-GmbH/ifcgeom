#include "ifcgeom/geometric_repr_item/geometric_set.h"

#include <variant>
#include <vector>

#include "utl/concat.h"
#include "utl/parser/cstr.h"

#include "IFC2X3/IfcCurve.h"
#include "IFC2X3/IfcGeometricCurveSet.h"
#include "IFC2X3/IfcGeometricSet.h"
#include "IFC2X3/IfcGeometricSetSelect.h"
#include "IFC2X3/IfcPoint.h"
#include "IFC2X3/IfcSurface.h"

#include "ifcgeom/geometric_repr_item/curve.h"
#include "ifcgeom/geometric_repr_item/point.h"
#include "ifcgeom/geometric_repr_item/surface.h"

#include "ifcgeom/core/match.h"

namespace ifcgeom {

std::vector<Point_3> geometric_set(IFC2X3::IfcGeometricSet const* set) {
  std::vector<Point_3> vertices;
  for (auto shell : set->Elements_) {
    std::visit(
        [&](auto item) {
          utl::concat(vertices, match(item, point_handler, curve_handler,
                                      surface_handler));
        },
        shell.data_);
  }
  return vertices;
}
std::vector<Point_3> geometric_crv_set(
    IFC2X3::IfcGeometricCurveSet const* set) {
  std::vector<Point_3> vertices;
  for (auto shell : set->Elements_) {
    std::visit(
        [&](auto item) {
          utl::concat(vertices, match(item, point_handler, curve_handler));
        },
        shell.data_);
  }
  return vertices;
}

std::vector<Point_3> geometric_set_handler(IFC2X3::IfcGeometricSet* set) {
  return match(set, geometric_crv_set, geometric_set);
}

}  // namespace ifcgeom