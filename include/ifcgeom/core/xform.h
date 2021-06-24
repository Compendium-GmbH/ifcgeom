#pragma once

#include "IFC2X3/IfcAxis2Placement2D.h"
#include "IFC2X3/IfcAxis2Placement3D.h"
#include "IFC2X3/IfcCartesianTransformationOperator.h"
#include "IFC2X3/IfcCartesianTransformationOperator2DnonUniform.h"
#include "IFC2X3/IfcCartesianTransformationOperator3DnonUniform.h"
#include "IFC2X3/IfcDirection.h"
#include "IFC2X3/IfcLocalPlacement.h"

#include "ifcgeom/core/utilities.h"

namespace ifcgeom {

inline Xform_3 matrix(IFC2X3::IfcAxis2Placement2D const* a2p) {
  auto axisZ = Vector_3{0, 0, 1};
  auto axisX = a2p->RefDirection_.has_value()
                   ? to_vector_3(a2p->RefDirection_.value())
                   : Vector_3{1, 0, 0};
  auto axisY = CGAL::cross_product(axisZ, axisX);
  Point_3 location = to_point_3(a2p->Location_);
  return Xform_3{axisX.x(), axisY.x(), axisZ.x(), location.x(),
                 axisX.y(), axisY.y(), axisZ.y(), location.y(),
                 axisX.z(), axisY.z(), axisZ.z(), location.z()};
}
inline Xform_3 matrix(IFC2X3::IfcAxis2Placement3D const* a2p) {
  auto axisZ = a2p->Axis_.has_value() ? to_vector_3(a2p->Axis_.value())
                                      : Vector_3{0, 0, 1};
  auto axisX = a2p->RefDirection_.has_value()
                   ? to_vector_3(a2p->RefDirection_.value())
                   : Vector_3{1, 0, 0};
  auto axisY = CGAL::cross_product(axisZ, axisX);
  normalize(axisY);  // TODO(Steffen): Testing
  Point_3 location = to_point_3(a2p->Location_);
  return Xform_3{axisX.x(), axisY.x(), axisZ.x(), location.x(),
                 axisX.y(), axisY.y(), axisZ.y(), location.y(),
                 axisX.z(), axisY.z(), axisZ.z(), location.z()};
}

inline Xform_3 h_transform(IFC2X3::IfcLocalPlacement const* lp) {
  Xform_3 res;
  if (lp->PlacementRelTo_.has_value()) {
    auto const rel_lp = reinterpret_cast<IFC2X3::IfcLocalPlacement const*>(
        lp->PlacementRelTo_.value());
    auto const rel_plcmt = rel_lp->RelativePlacement_.data_;
    Xform_3 xform;
    if (std::holds_alternative<IFC2X3::IfcAxis2Placement2D*>(rel_plcmt)) {
      xform = matrix(std::get<IFC2X3::IfcAxis2Placement2D*>(rel_plcmt));
    } else {
      xform = matrix(std::get<IFC2X3::IfcAxis2Placement3D*>(rel_plcmt));
    }
    res = xform * h_transform(rel_lp);
  } else {
    res = Xform_3{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0};
  }
  return res;
}

inline Xform_3 cartesian_transformation(
    IFC2X3::IfcCartesianTransformationOperator const* cto) {
  auto axisX = cto->Axis1_.has_value() ? to_vector_3(cto->Axis1_.value())
                                       : Vector_3{1, 0, 0};
  auto axisY = cto->Axis2_.has_value() ? to_vector_3(cto->Axis2_.value())
                                       : Vector_3{0, 1, 0};
  auto axisZ = CGAL::cross_product(axisY, axisX);

  auto const scale = cto->Scale_.has_value() ? cto->Scale_.value() : 1.0;

  ifcgeom::normalize(axisX, axisY, axisZ);

  axisX = scale * axisX;
  axisY = scale * axisY;
  axisZ = scale * axisZ;

  auto const xform =
      Xform_3{axisX.x(), axisY.x(),
              axisZ.x(), cto->LocalOrigin_->Coordinates_.at(0) * scale,
              axisX.y(), axisY.y(),
              axisZ.y(), cto->LocalOrigin_->Coordinates_.at(1) * scale,
              axisX.z(), axisY.z(),
              axisZ.z(), cto->LocalOrigin_->Coordinates_.at(2) * scale};

  return xform;
}

inline Xform_3 cartesian_transformation_non_uniform(
    IFC2X3::IfcCartesianTransformationOperator3DnonUniform const* cto) {
  return Xform_3{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0};
}

inline Xform_3 cartesian_transformation_non_uniform(
    IFC2X3::IfcCartesianTransformationOperator2DnonUniform const* cto) {
  return Xform_3{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0};
}

}  // namespace ifcgeom
