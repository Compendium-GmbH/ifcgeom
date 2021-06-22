#pragma once

#include <vector>

#include "IFC2X3/IfcAxis1Placement.h"
#include "IFC2X3/IfcAxis2Placement2D.h"
#include "IFC2X3/IfcAxis2Placement3D.h"
#include "IFC2X3/IfcCartesianPoint.h"
#include "IFC2X3/IfcCartesianTransformationOperator.h"
#include "IFC2X3/IfcDirection.h"
#include "IFC2X3/IfcLocalPlacement.h"
#include "IFC2X3/IfcMappedItem.h"
#include "IFC2X3/IfcObjectPlacement.h"
#include "IFC2X3/IfcPlacement.h"
#include "IFC2X3/IfcPolyline.h"
#include "IFC2X3/IfcRepresentationMap.h"

#include "CGAL/Aff_transformation_3.h"
#include "CGAL/aff_transformation_tags.h"

#include "ifcgeom/core/context.h"

namespace ifcgeom {

inline Point_3 to_point_3(IFC2X3::IfcCartesianPoint const* cp) {
  return Point_3{cp->Coordinates_.at(0), cp->Coordinates_.at(1),
                 cp->Coordinates_.size() == 3 ? cp->Coordinates_.at(2) : 0};
}
inline Point_3 to_point_3(IFC2X3::IfcDirection const* dir) {
  return Point_3{
      dir->DirectionRatios_.at(0), dir->DirectionRatios_.at(1),
      dir->DirectionRatios_.size() == 3 ? dir->DirectionRatios_.at(2) : 0};
}
inline Vector_3 to_vector_3(IFC2X3::IfcDirection const* dir) {
  return Vector_3{
      dir->DirectionRatios_.at(0), dir->DirectionRatios_.at(1),
      dir->DirectionRatios_.size() == 3 ? dir->DirectionRatios_.at(2) : 0};
}
inline Vector_3 to_vector_3(Point_3 const& pt) {
  return Vector_3{pt.x(), pt.y(), pt.z()};
}
inline Direction_3 to_direction_3(IFC2X3::IfcDirection const* dir) {
  return Direction_3{
      dir->DirectionRatios_.at(0), dir->DirectionRatios_.at(1),
      dir->DirectionRatios_.size() == 3 ? dir->DirectionRatios_.at(2) : 0};
}
inline Point_2 to_point_2(IFC2X3::IfcCartesianPoint const* cp) {
  return Point_2{cp->Coordinates_.at(0), cp->Coordinates_.at(1)};
}

inline void print(Point_3 const& pt) {
  std::cout << "Point_3 : X=" << pt.x() << " Y=" << pt.y() << " Z=" << pt.z()
            << std::endl;
}
inline void print(Vector_3 const& vec) {
  std::cout << "Point_3 : X=" << vec.x() << " Y=" << vec.y() << " Z=" << vec.z()
            << std::endl;
}
inline void print(Direction_3 const& dir) {
  std::cout << "Point_3 : X=" << dir.vector().x() << " Y=" << dir.vector().y()
            << " Z=" << dir.vector().z() << std::endl;
}
inline void print(Xform_3 const& xform3) {
  std::cout << "------------------" << std::endl;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      std::cout << xform3.m(i, j) << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "------------------" << std::endl;
}
inline void print(std::vector<Point_3> const& geometry) {
  for (auto const& pt : geometry) {
    print(pt);
  }
}
inline void print(std::vector<std::vector<Point_3>> const& geo) {
  for (size_t i = 0; i < geo.size(); ++i) {
    std::cout << "Geometry [" << i + 1 << "/" << geo.size() << "]" << std::endl;
    print(geo.at(i));
    std::cout << std::endl;
  }
}
inline void print(IFC2X3::IfcCartesianPoint const* cp) {
  auto z = cp->Coordinates_.size() == 3 ? cp->Coordinates_.at(2) : 0;
  std::cout << "IFC2X3::IfcCartesianPoint : X=" << cp->Coordinates_.at(0)
            << " Y=" << cp->Coordinates_.at(1) << " Z=" << z << std::endl;
}

inline void normalize(Vector_3& vec) {
  auto s_length = vec.squared_length();
  vec /= std::sqrt(s_length);
}

inline std::vector<Point_3> points_from_polyline(
    IFC2X3::IfcPolyline const* polyline) {
  std::vector<Point_3> points;
  for (size_t i = 0; i < polyline->Points_.size() - 1; ++i) {
    points.emplace_back(to_point_3(polyline->Points_.at(i)));
  }
  return points;
}
inline std::vector<Point_3> points_from_circle(
    IFC2X3::IfcCartesianPoint const* cp, double const& radius) {
  auto const pos = cp->Coordinates_;
  auto const step = M_PI * 2 / render_resolution;
  std::vector<Point_3> pts;
  for (unsigned i = 0; i < render_resolution; ++i) {
    auto x = radius * std::cos(step * i) + pos.at(0);
    auto y = radius * std::sin(step * i) + pos.at(1);
    pts.emplace_back(Point_3{x, y, pos.size() == 3 ? pos.at(2) : 0});
  }
  return pts;
}

inline std::vector<Point_3> translate(IFC2X3::IfcPolyline const* polyline,
                                      Vector_3 d) {
  auto points = points_from_polyline(polyline);
  for (auto& point : points) {
    point += d;
  }
  return points;
}
inline std::vector<Point_3> translate(std::vector<Point_3> const& pts,
                                      Vector_3 d) {
  auto points = std::vector<Point_3>{pts};
  for (auto& point : points) {
    point += d;
  }
  return points;
}

// Returns the Rotation of a given point around axis with an angle in degrees.
// Assumes axis is normalized.
// Assumes angle in degrees.
inline Point_3 rotate(Point_3 const& pt, IFC2X3::IfcAxis1Placement const* a1p,
                      double const& angle_deg) {
  // get axis
  auto const axis = a1p->Axis_.has_value() ? to_vector_3(a1p->Axis_.value())
                                           : Vector_3{1, 0, 0};

  double constexpr deg_to_rad = M_PI / 180;
  double const angle_rad = angle_deg * deg_to_rad;
  // precompute angle
  double const cos_angle = std::cos(angle_rad);
  double const one_minus_cos_angle = 1.0 - cos_angle;
  double const sin_angle = std::sin(angle_rad);

  Xform_3 rotation_matrix{
      cos_angle + axis.x() * axis.x() * one_minus_cos_angle,
      axis.x() * axis.y() * one_minus_cos_angle - axis.z() * sin_angle,
      axis.x() * axis.z() * one_minus_cos_angle + axis.y() * sin_angle,
      0,
      axis.y() * axis.x() * one_minus_cos_angle + axis.z() * sin_angle,
      cos_angle + axis.y() * axis.y() * one_minus_cos_angle,
      axis.y() * axis.z() * one_minus_cos_angle - axis.x() * sin_angle,
      0,
      axis.z() * axis.x() * one_minus_cos_angle - axis.y() * sin_angle,
      axis.z() * axis.y() * one_minus_cos_angle + axis.x() * sin_angle,
      cos_angle + axis.z() * axis.z() * one_minus_cos_angle,
      0};

  return rotation_matrix.transform(pt);
}
}  // namespace ifcgeom
