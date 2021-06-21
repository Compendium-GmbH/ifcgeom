#include "ifcgeom/geometric_repr_item/curve.h"

#include "utl/concat.h"

#include "IFC2X3/Ifc2DCompositeCurve.h"
#include "IFC2X3/IfcBezierCurve.h"
#include "IFC2X3/IfcCircle.h"
#include "IFC2X3/IfcCompositeCurve.h"
#include "IFC2X3/IfcEllipse.h"
#include "IFC2X3/IfcLine.h"
#include "IFC2X3/IfcOffsetCurve2D.h"
#include "IFC2X3/IfcOffsetCurve3D.h"
#include "IFC2X3/IfcPolyline.h"
#include "IFC2X3/IfcRationalBezierCurve.h"
#include "IFC2X3/IfcTrimmedCurve.h"

#include "ifcgeom/core/context.h"
#include "ifcgeom/core/match.h"
#include "ifcgeom/core/utilities.h"

#include "ifcgeom/geometric_repr_item/composite_crv_segment.h"

namespace ifcgeom {

#pragma region IfcBoundedCurve

std::vector<Point_3> composite_crv(IFC2X3::IfcCompositeCurve const* crv) {
  std::vector<Point_3> vertices;
  for (auto const segment : crv->Segments_) {
    utl::concat(vertices, composite_crv_segment(segment));
  }
  return vertices;
}
std::vector<Point_3> composite_crv_2d(IFC2X3::Ifc2DCompositeCurve const* crv) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{crv->name()});
  return vertices;
}
std::vector<Point_3> polyline(IFC2X3::IfcPolyline const* crv) {
  std::vector<Point_3> vertices;
  for (auto const pt : crv->Points_) {
    vertices.emplace_back(to_point_3(pt));
  }
  return vertices;
}
std::vector<Point_3> trimmed_crv(IFC2X3::IfcTrimmedCurve const* crv) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{crv->name()});
  return vertices;
}
std::vector<Point_3> bezier_crv(IFC2X3::IfcBezierCurve const* crv) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{crv->name()});
  return vertices;
}
std::vector<Point_3> rational_bezier_crv(
    IFC2X3::IfcRationalBezierCurve const* crv) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{crv->name()});
  return vertices;
}

#pragma endregion

#pragma region IfcConic

std::vector<Point_3> circle(IFC2X3::IfcCircle const* crv) {
  std::vector<Point_3> vertices;

  render_err_log.emplace_back(std::string{crv->name()});
  return vertices;
}
std::vector<Point_3> ellipse(IFC2X3::IfcEllipse const* crv) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{crv->name()});
  return vertices;
}

#pragma endregion

#pragma region IfcLine

std::vector<Point_3> line(IFC2X3::IfcLine const* crv) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{crv->name()});
  return vertices;
}

#pragma endregion

#pragma region IfcOffsetCurve

std::vector<Point_3> offset_crv_2d(IFC2X3::IfcOffsetCurve2D const* crv) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{crv->name()});
  return vertices;
}
std::vector<Point_3> offset_crv_3d(IFC2X3::IfcOffsetCurve3D const* crv) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{crv->name()});
  return vertices;
}

#pragma endregion

std::vector<Point_3> curve_handler(IFC2X3::IfcCurve* item) {
  return match(item,
               // IfcBoundedCurve
               composite_crv_2d, composite_crv, polyline, trimmed_crv,
               rational_bezier_crv, bezier_crv,
               // IfcConic
               circle, ellipse,
               // IfcLine
               line,
               // IfcOffsetCurve
               offset_crv_2d, offset_crv_3d);
}

}  // namespace ifcgeom
