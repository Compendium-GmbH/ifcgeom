#include "ifcgeom/geometric_repr_item/profile_def.h"

#include "IFC2X3/IfcArbitraryClosedProfileDef.h"
#include "IFC2X3/IfcArbitraryProfileDefWithVoids.h"
#include "IFC2X3/IfcAxis2Placement2D.h"
#include "IFC2X3/IfcCShapeProfileDef.h"
#include "IFC2X3/IfcCenterLineProfileDef.h"
#include "IFC2X3/IfcCircleHollowProfileDef.h"
#include "IFC2X3/IfcCircleProfileDef.h"
#include "IFC2X3/IfcCompositeProfileDef.h"
#include "IFC2X3/IfcCraneRailAShapeProfileDef.h"
#include "IFC2X3/IfcCraneRailFShapeProfileDef.h"
#include "IFC2X3/IfcDerivedProfileDef.h"
#include "IFC2X3/IfcEllipseProfileDef.h"
#include "IFC2X3/IfcIShapeProfileDef.h"
#include "IFC2X3/IfcLShapeProfileDef.h"
#include "IFC2X3/IfcProfileDef.h"
#include "IFC2X3/IfcRectangleProfileDef.h"
#include "IFC2X3/IfcTShapeProfileDef.h"
#include "IFC2X3/IfcTrapeziumProfileDef.h"
#include "IFC2X3/IfcUShapeProfileDef.h"
#include "IFC2X3/IfcZShapeProfileDef.h"

#include "ifcgeom/geometric_repr_item/curve.h"

#include "ifcgeom/core/context.h"
#include "ifcgeom/core/match.h"
#include "ifcgeom/core/utilities.h"

namespace ifcgeom {

#pragma region IfcParameterizedProfileDef

std::vector<Point_3> i_shape_profile_def(
    IFC2X3::IfcIShapeProfileDef const* profile) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{profile->name()});
  return vertices;
}
std::vector<Point_3> l_shape_profile_def(
    IFC2X3::IfcLShapeProfileDef const* profile) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{profile->name()});
  return vertices;
}
std::vector<Point_3> u_shape_profile_def(
    IFC2X3::IfcUShapeProfileDef const* profile) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{profile->name()});
  return vertices;
}
std::vector<Point_3> z_shape_profile_def(
    IFC2X3::IfcZShapeProfileDef const* profile) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{profile->name()});
  return vertices;
}
std::vector<Point_3> t_shape_profile_def(
    IFC2X3::IfcTShapeProfileDef const* profile) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{profile->name()});
  return vertices;
}
std::vector<Point_3> crane_rail_f_shape_profile_def(
    IFC2X3::IfcCraneRailFShapeProfileDef const* profile) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{profile->name()});
  return vertices;
}
std::vector<Point_3> crane_rail_a_shape_profile_def(
    IFC2X3::IfcCraneRailAShapeProfileDef const* profile) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{profile->name()});
  return vertices;
}
std::vector<Point_3> circle_profile_def(
    IFC2X3::IfcCircleProfileDef const* profile) {
  std::vector<Point_3> vertices;
  auto pts =
      points_from_circle(profile->Position_->Location_, profile->Radius_);
  vertices.insert(vertices.end(), pts.begin(), pts.end());
  return vertices;
}
std::vector<Point_3> circle_hollow_profile_def(
    IFC2X3::IfcCircleHollowProfileDef const* profile) {
  std::vector<Point_3> vertices;
  auto outer_pts =
      points_from_circle(profile->Position_->Location_, profile->Radius_);
  auto inner_pts =
      points_from_circle(profile->Position_->Location_,
                         profile->Radius_ - profile->WallThickness_);
  vertices.insert(vertices.end(), outer_pts.begin(), outer_pts.end());
  vertices.insert(vertices.end(), inner_pts.begin(), inner_pts.end());
  return vertices;
}
std::vector<Point_3> ellipse_profile_def(
    IFC2X3::IfcEllipseProfileDef const* profile) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{profile->name()});
  return vertices;
}
std::vector<Point_3> rectangle_profile_def(
    IFC2X3::IfcRectangleProfileDef const* profile) {
  std::vector<Point_3> vertices;
  auto const ref = profile->Position_->RefDirection_;
  auto pos = to_point_3(profile->Position_->Location_);
  auto vec_x = ref.has_value() ? to_vector_3(ref.value()) : Vector_3{1, 0, 0};
  auto vec_y = CGAL::cross_product(Vector_3{0, 0, 1}, vec_x);
  normalize(vec_x);
  normalize(vec_y);

  auto t1 = Vector_3{profile->XDim_ / 2, profile->YDim_ / 2, 0};
  auto t2 = Vector_3{profile->XDim_ / 2, -profile->YDim_ / 2, 0};

  std::vector<Point_3> pts{pos - t1, pos + t2, pos + t1, pos - t2};
  vertices.insert(vertices.end(), pts.begin(), pts.end());
  return vertices;
}
std::vector<Point_3> trapezium_profile_def(
    IFC2X3::IfcTrapeziumProfileDef const* profile) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{profile->name()});
  return vertices;
}

#pragma endregion

#pragma region IfcArbitraryOpenProfileDef

std::vector<Point_3> center_line_profile_def(
    IFC2X3::IfcCenterLineProfileDef const* profile) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{profile->name()});
  return vertices;
}

#pragma endregion

#pragma region IfcArbitraryClosedProfileDef

std::vector<Point_3> arbitrary_profile_def(
    IFC2X3::IfcArbitraryClosedProfileDef const* profile) {
  return curve_handler(profile->OuterCurve_);
}
std::vector<Point_3> arbitrary_profile_def_with_voids(
    IFC2X3::IfcArbitraryProfileDefWithVoids const* profile) {
  // TODO(ANYONE): IMPLEMENT VOIDS !
  return curve_handler(profile->OuterCurve_);
}

#pragma endregion

#pragma region IfcCompositeProfileDef

std::vector<Point_3> composite_profile_def(
    IFC2X3::IfcCompositeProfileDef const* profile) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{profile->name()});
  return vertices;
}

#pragma endregion

#pragma region IfcDerivedProfileDef

std::vector<Point_3> derived_profile_def(
    IFC2X3::IfcDerivedProfileDef const* profile) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{profile->name()});
  return vertices;
}

#pragma endregion

std::vector<Point_3> profile_def_handler(IFC2X3::IfcProfileDef* profile_def) {
  return match(profile_def,
               // IfcParameterizedProfileDef
               i_shape_profile_def, l_shape_profile_def, u_shape_profile_def,
               z_shape_profile_def, t_shape_profile_def,
               crane_rail_f_shape_profile_def, crane_rail_a_shape_profile_def,
               circle_hollow_profile_def, circle_profile_def,
               ellipse_profile_def, rectangle_profile_def,
               trapezium_profile_def,
               // IfcArbitraryOpenProfileDef
               center_line_profile_def,
               // IfcArbitraryClosedProfileDef
               arbitrary_profile_def_with_voids, arbitrary_profile_def,
               // IfcCompositeProfileDef
               composite_profile_def,
               // IfcDerivedProfileDef
               derived_profile_def);
}

}  // namespace ifcgeom
