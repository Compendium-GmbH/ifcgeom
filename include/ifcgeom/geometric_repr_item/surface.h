#pragma once

#include <vector>

#include "utl/concat.h"
#include "utl/parser/cstr.h"

#include "IFC2X3/IfcBoundedSurface.h"
#include "IFC2X3/IfcCurveBoundedPlane.h"
#include "IFC2X3/IfcPlane.h"
#include "IFC2X3/IfcRectangularTrimmedSurface.h"
#include "IFC2X3/IfcSurfaceOfLinearExtrusion.h"
#include "IFC2X3/IfcSurfaceOfRevolution.h"

#include "ifcgeom/core/context.h"

namespace ifcgeom {

#pragma region IfcElementarySurface

std::vector<Point_3> plane(IFC2X3::IfcPlane const* srf) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{srf->name()}, __func__);
  return vertices;
}

#pragma endregion

#pragma region IfcSweptSurface

std::vector<Point_3> srf_of_revolve(IFC2X3::IfcSurfaceOfRevolution const* srf) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{srf->name()}, __func__);
  return vertices;
}
std::vector<Point_3> srf_of_extrude(
    IFC2X3::IfcSurfaceOfLinearExtrusion const* srf) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{srf->name()}, __func__);
  return vertices;
}

#pragma endregion

#pragma region IfcBoundedSurface

std::vector<Point_3> bounded_srf(IFC2X3::IfcBoundedSurface const* srf) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{srf->name()}, __func__);
  return vertices;
}
std::vector<Point_3> crv_bounded_plane(
    IFC2X3::IfcCurveBoundedPlane const* srf) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{srf->name()}, __func__);
  return vertices;
}
std::vector<Point_3> rect_trimmed_srf(
    IFC2X3::IfcRectangularTrimmedSurface const* srf) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{srf->name()}, __func__);
  return vertices;
}

#pragma endregion

std::vector<Point_3> surface_handler(IFC2X3::IfcSurface* item) {
  std::vector<Point_3> vertices{};
  utl::concat(vertices,
              match(item, plane, srf_of_revolve, srf_of_extrude,
                    crv_bounded_plane, rect_trimmed_srf, bounded_srf));
  return vertices;
}

}  // namespace ifcgeom
