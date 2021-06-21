#pragma once

#include "IFC2X3/IfcArbitraryClosedProfileDef.h"
#include "IFC2X3/IfcArbitraryProfileDefWithVoids.h"
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

#include "ifcgeom/core/types.h"

namespace ifcgeom {

std::vector<Point_3> i_shape_profile_def(
    IFC2X3::IfcIShapeProfileDef const* profile);
std::vector<Point_3> l_shape_profile_def(
    IFC2X3::IfcLShapeProfileDef const* profile);
std::vector<Point_3> u_shape_profile_def(
    IFC2X3::IfcUShapeProfileDef const* profile);
std::vector<Point_3> z_shape_profile_def(
    IFC2X3::IfcZShapeProfileDef const* profile);
std::vector<Point_3> t_shape_profile_def(
    IFC2X3::IfcTShapeProfileDef const* profile);
std::vector<Point_3> crane_rail_f_shape_profile_def(
    IFC2X3::IfcCraneRailFShapeProfileDef const* profile);
std::vector<Point_3> crane_rail_a_shape_profile_def(
    IFC2X3::IfcCraneRailAShapeProfileDef const* profile);
std::vector<Point_3> circle_profile_def(
    IFC2X3::IfcCircleProfileDef const* profile);
std::vector<Point_3> circle_hollow_profile_def(
    IFC2X3::IfcCircleHollowProfileDef const* profile);
std::vector<Point_3> ellipse_profile_def(
    IFC2X3::IfcEllipseProfileDef const* profile);
std::vector<Point_3> rectangle_profile_def(
    IFC2X3::IfcRectangleProfileDef const* profile);
std::vector<Point_3> trapezium_profile_def(
    IFC2X3::IfcTrapeziumProfileDef const* profile);

std::vector<Point_3> center_line_profile_def(
    IFC2X3::IfcCenterLineProfileDef const* profile);

std::vector<Point_3> arbitrary_profile_def(
    IFC2X3::IfcArbitraryClosedProfileDef const* profile);
std::vector<Point_3> arbitrary_profile_def_with_voids(
    IFC2X3::IfcArbitraryProfileDefWithVoids const* profile);

std::vector<Point_3> composite_profile_def(
    IFC2X3::IfcCompositeProfileDef const* profile);

std::vector<Point_3> derived_profile_def(
    IFC2X3::IfcDerivedProfileDef const* profile);

std::vector<Point_3> profile_def_handler(IFC2X3::IfcProfileDef* profile_def);

}  // namespace ifcgeom
