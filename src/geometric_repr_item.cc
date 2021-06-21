#include "ifcgeom/geometric_repr_item.h"

#include <type_traits>
#include <variant>
#include <vector>

#include "utl/concat.h"
#include "utl/parser/cstr.h"

#include "IFC2X3/IfcBoundingBox.h"
#include "IFC2X3/IfcCompositeCurveSegment.h"
#include "IFC2X3/IfcDirection.h"
#include "IFC2X3/IfcFaceBasedSurfaceModel.h"
#include "IFC2X3/IfcSectionedSpine.h"
#include "IFC2X3/IfcShell.h"
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

#include "ifcgeom/geometric_repr_item/composite_crv_segment.h"
#include "ifcgeom/topological_repr_item/connected_face_set.h"

#include "ifcgeom/core/context.h"
#include "ifcgeom/core/match.h"
#include "ifcgeom/core/utilities.h"

namespace ifcgeom {

std::vector<Point_3> direction(IFC2X3::IfcDirection const* dir) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{dir->name()});
  return vertices;
}

std::vector<Point_3> vector(IFC2X3::IfcVector const* v) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{v->name()});
  return vertices;
}

std::vector<Point_3> bounding_box(IFC2X3::IfcBoundingBox const* bbox) {
  auto const c = to_point_3(bbox->Corner_);
  std::vector<Point_3> vertices{c, c + Vector_3{bbox->XDim_, 0, 0},
                                c + Vector_3{bbox->XDim_, bbox->YDim_, 0},
                                c + Vector_3{0, bbox->YDim_, 0}};
  utl::concat(vertices, translate(vertices, Vector_3{0, 0, bbox->ZDim_}));
  return vertices;
}

std::vector<Point_3> sectioned_spine(IFC2X3::IfcSectionedSpine const* spine) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{spine->name()});
  return vertices;
}

std::vector<Point_3> face_based_srf_model(
    IFC2X3::IfcFaceBasedSurfaceModel const* srf) {
  std::vector<Point_3> vertices;
  for (auto const face_set : srf->FbsmFaces_) {
    utl::concat(vertices, connected_face_set_handler(face_set));
  }
  return vertices;
}

std::vector<Point_3> shell_based_srf_model(
    IFC2X3::IfcShellBasedSurfaceModel const* srf) {
  std::vector<Point_3> vertices;
  for (auto shell : srf->SbsmBoundary_) {
    std::visit(
        [&](auto item) {
          utl::concat(vertices, match(item, open_shell, closed_shell));
        },
        shell.data_);
  }
  return vertices;
}

std::vector<Point_3> geometric_repr_item_handler(
    IFC2X3::IfcGeometricRepresentationItem* item) {
  return match(
      item, composite_crv_segment, curve_handler, direction, placement_handler,
      point_handler, surface_handler, vector, boolean_result_handler,
      solid_model_handler, half_space_solid_handler, bounding_box,
      crt_xform_operator_handler, sectioned_spine, geometric_set_handler,
      face_based_srf_model, shell_based_srf_model);
}

}  // namespace ifcgeom
