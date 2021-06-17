#pragma once

#include <variant>
#include <vector>

#include "utl/concat.h"
#include "utl/parser/cstr.h"

#include "IFC2X3/IfcCompositeCurveSegment.h"

namespace ifcgeom {

std::vector<Point_3> composite_crv_segment(
    IFC2X3::IfcCompositeCurveSegment const* crv) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{crv->name()});
  return vertices;
}

}  // namespace ifcgeom