#pragma once

#include <vector>

#include "utl/concat.h"
#include "utl/parser/cstr.h"

#include "IFC2X3/IfcCartesianTransformationOperator.h"
#include "IFC2X3/IfcCartesianTransformationOperator2D.h"
#include "IFC2X3/IfcCartesianTransformationOperator2DnonUniform.h"
#include "IFC2X3/IfcCartesianTransformationOperator3D.h"
#include "IFC2X3/IfcCartesianTransformationOperator3DnonUniform.h"

#include "ifcgeom/core/match.h"

namespace ifcgeom {

std::vector<Point_3> cartesian_xform_operator_2d(
    IFC2X3::IfcCartesianTransformationOperator2D const* op) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{op->name()});
  return vertices;
}
std::vector<Point_3> cartesian_xform_operator_2d_nu(
    IFC2X3::IfcCartesianTransformationOperator2DnonUniform const* op) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{op->name()});
  return vertices;
}
std::vector<Point_3> cartesian_xform_operator_3d(
    IFC2X3::IfcCartesianTransformationOperator3D const* op) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{op->name()});
  return vertices;
}
std::vector<Point_3> cartesian_xform_operator_3d_nu(
    IFC2X3::IfcCartesianTransformationOperator3DnonUniform const* op) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{op->name()});
  return vertices;
}

std::vector<Point_3> crt_xform_operator_handler(
    IFC2X3::IfcCartesianTransformationOperator* item) {
  return match(item, cartesian_xform_operator_2d_nu,
               cartesian_xform_operator_2d, cartesian_xform_operator_3d_nu,
               cartesian_xform_operator_3d);
}

}  // namespace ifcgeom
