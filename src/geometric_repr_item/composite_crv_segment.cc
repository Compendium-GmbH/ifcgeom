#include "ifcgeom/geometric_repr_item/composite_crv_segment.h"

#include <vector>

#include "ifcgeom/core/context.h"

namespace ifcgeom {

std::vector<Point_3> composite_crv_segment(
    IFC2X3::IfcCompositeCurveSegment const* crv) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{crv->name()});
  return vertices;
}

}  // namespace ifcgeom