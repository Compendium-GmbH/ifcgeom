#include "IFC2X3/IfcAxis2Placement2D.h"
#include "IFC2X3/IfcAxis2Placement3D.h"
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
  // clang-format off
  return Xform_3{axisX.x(), axisY.x(), axisZ.x(), location.x(),
                 axisX.y(), axisY.y(), axisZ.y(), location.y(),
                 axisX.z(), axisY.z(), axisZ.z(), location.z()};
  // clang-format on
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

inline void find_placement(IFC2X3::IfcProduct const* elem) {
  auto const local_plcmt = reinterpret_cast<IFC2X3::IfcLocalPlacement const*>(
      elem->ObjectPlacement_.value());
  auto const a2p3d = std::get<IFC2X3::IfcAxis2Placement3D*>(
      local_plcmt->RelativePlacement_.data_);

  auto const location_p3 = to_point_3(a2p3d->Location_);

  auto const ht = h_transform(local_plcmt);
  auto p = ht.transform(location_p3);
}

}  // namespace ifcgeom
