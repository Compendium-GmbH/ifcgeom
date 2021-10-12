#include "ifcgeom/geometric_repr_item/solid_model.h"

#include "utl/concat.h"

#include "IFC2X3/IfcAxis1Placement.h"
#include "IFC2X3/IfcAxis2Placement2D.h"
#include "IFC2X3/IfcAxis2Placement3D.h"
#include "IFC2X3/IfcClosedShell.h"
#include "IFC2X3/IfcCsgSolid.h"
#include "IFC2X3/IfcExtrudedAreaSolid.h"
#include "IFC2X3/IfcFace.h"
#include "IFC2X3/IfcFaceBound.h"
#include "IFC2X3/IfcFacetedBrep.h"
#include "IFC2X3/IfcFacetedBrepWithVoids.h"
#include "IFC2X3/IfcPolyline.h"
#include "IFC2X3/IfcRepresentationItem.h"
#include "IFC2X3/IfcRevolvedAreaSolid.h"
#include "IFC2X3/IfcSurfaceCurveSweptAreaSolid.h"
#include "IFC2X3/IfcSweptDiskSolid.h"

#include "ifcgeom/core/context.h"
#include "ifcgeom/core/match.h"
#include "ifcgeom/core/utilities.h"
#include "ifcgeom/core/xform.h"

#include "ifcgeom/geometric_repr_item/profile_def.h"
#include "ifcgeom/topological_repr_item/loop.h"

namespace ifcgeom {

#pragma region IfcManifoldSolidBrep

std::vector<Point_3> faceted_brep(IFC2X3::IfcFacetedBrep const* brep) {
  std::vector<Point_3> vertices;
  for (auto const face : brep->Outer_->CfsFaces_) {
    auto const bounds = face->Bounds_;
    for (auto const bound : bounds) {
      utl::concat(vertices,
                  match(bound->Bound_, poly_loop, vertex_loop, edge_loop));
    }
  }
  return vertices;
}

std::vector<Point_3> faceted_brep_with_voids(
    IFC2X3::IfcFacetedBrepWithVoids const* brep) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{brep->name()});
  return vertices;
}

#pragma endregion

#pragma region IfcSweptAreaSolid

std::vector<Point_3> extruded_area(IFC2X3::IfcExtrudedAreaSolid const* ext) {
  // extruded direction and depth
  auto extrude_dir = to_vector_3(ext->ExtrudedDirection_);
  normalize(extrude_dir);
  extrude_dir *= ext->Depth_;

  // swept area
  std::vector<Point_3> vertices{};
  utl::concat(vertices, profile_def_handler(ext->SweptArea_));
  auto t_pts = translate(vertices, extrude_dir);
  vertices.insert(vertices.end(), t_pts.begin(), t_pts.end());

  auto vertices_tr = ifcgeom::cartesian_transformation(
      ifcgeom::matrix(ext->Position_), vertices);

  return vertices_tr;
}

std::vector<Point_3> revolved_area(
    IFC2X3::IfcRevolvedAreaSolid const* revolved) {
  std::vector<Point_3> vertices;
  auto swept_area = profile_def_handler(revolved->SweptArea_);
  render_err_log.emplace_back(std::string{revolved->name()});
  return vertices;
}

std::vector<Point_3> surface_curve(
    IFC2X3::IfcSurfaceCurveSweptAreaSolid const* crv) {
  render_err_log.emplace_back(std::string{crv->name()});
  return std::vector<Point_3>{};
}

#pragma endregion

#pragma region IfcCsgSolid

std::vector<Point_3> csg_solid(IFC2X3::IfcCsgSolid const* csg) {
  render_err_log.emplace_back(std::string{csg->name()});
  return std::vector<Point_3>{};
}

#pragma endregion

#pragma region IfcSweptDiskSolid

std::vector<Point_3> swept_disk(IFC2X3::IfcSweptDiskSolid const* swept) {
  render_err_log.emplace_back(std::string{swept->name()});
  return std::vector<Point_3>{};
}

#pragma endregion

std::vector<Point_3> solid_model_handler(IFC2X3::IfcSolidModel* item) {
  return match(item,
               // IfcManifoldSolidBrep
               faceted_brep_with_voids, faceted_brep,
               // IfcSweptAreaSolid
               extruded_area, revolved_area, surface_curve,
               // IfcCsgSolid
               csg_solid,
               // IfcSweptDiskSolid
               swept_disk);
}

}  // namespace ifcgeom
