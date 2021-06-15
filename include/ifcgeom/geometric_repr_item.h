#pragma once

#include <vector>

#include "utl/concat.h"
#include "utl/parser/cstr.h"

#include "IFC2X3/IfcBoundingBox.h"
#include "IFC2X3/IfcCompositeCurveSegment.h"
#include "IFC2X3/IfcDirection.h"
#include "IFC2X3/IfcFaceBasedSurfaceModel.h"
#include "IFC2X3/IfcSectionedSpine.h"
#include "IFC2X3/IfcShellBasedSurfaceModel.h"
#include "IFC2X3/IfcVector.h"

#include "ifcgeom/geometric_repr_item/boolean_result.h"
#include "ifcgeom/geometric_repr_item/crt_xform_operator.h"
#include "ifcgeom/geometric_repr_item/curve.h"
#include "ifcgeom/geometric_repr_item/geometric_set.h"
#include "ifcgeom/geometric_repr_item/half_space_solid.h"
#include "ifcgeom/geometric_repr_item/placement.h"
#include "ifcgeom/geometric_repr_item/point.h"
#include "ifcgeom/geometric_repr_item/solid_model.h"
#include "ifcgeom/geometric_repr_item/surface.h"

#include "ifcgeom/core/match.h"

namespace ifcgeom {

std::vector<Point_3> composite_crv_segment(
    IFC2X3::IfcCompositeCurveSegment const* crv) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{crv->name()}, __func__);
  return vertices;
}
// OBSOLETE...
std::vector<Point_3> direction(IFC2X3::IfcDirection const* dir) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{dir->name()}, __func__);
  return vertices;
}
// OBSOLETE...
std::vector<Point_3> vector(IFC2X3::IfcVector const* v) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{v->name()}, __func__);
  return vertices;
}

std::vector<Point_3> bounding_box(IFC2X3::IfcBoundingBox const* bbox) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{bbox->name()}, __func__);
  return vertices;
}

std::vector<Point_3> sectioned_spine(IFC2X3::IfcSectionedSpine const* spine) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{spine->name()}, __func__);
  return vertices;
}

std::vector<Point_3> face_based_srf_model(
    IFC2X3::IfcFaceBasedSurfaceModel const* srf) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{srf->name()}, __func__);
  return vertices;
}

std::vector<Point_3> shell_based_srf_model(
    IFC2X3::IfcShellBasedSurfaceModel const* srf) {
  std::vector<Point_3> vertices;
  add_to_map(render_err_log_, std::string{srf->name()}, __func__);
  return vertices;
}

std::vector<Point_3> geometric_repr_item_handler(
    IFC2X3::IfcGeometricRepresentationItem* item) {
  std::vector<Point_3> vertices{};
  utl::concat(vertices, match(item, composite_crv_segment, curve_handler,
                              direction, placement_handler, point_handler,
                              surface_handler, vector, boolean_result_handler,
                              solid_model_handler, half_space_solid_handler,
                              bounding_box, crt_xform_operator_handler,
                              sectioned_spine, geometric_set_handler,
                              face_based_srf_model, shell_based_srf_model));
  return vertices;
}

}  // namespace ifcgeom
