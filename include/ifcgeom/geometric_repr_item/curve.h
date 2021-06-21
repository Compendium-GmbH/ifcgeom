#pragma once

#include "step/exp_logical.h"

#include "IFC2X3/Ifc2DCompositeCurve.h"
#include "IFC2X3/IfcBezierCurve.h"
#include "IFC2X3/IfcCircle.h"
#include "IFC2X3/IfcCompositeCurve.h"
#include "IFC2X3/IfcEllipse.h"
#include "IFC2X3/IfcLine.h"
#include "IFC2X3/IfcOffsetCurve2D.h"
#include "IFC2X3/IfcOffsetCurve3D.h"
#include "IFC2X3/IfcPolyline.h"
#include "IFC2X3/IfcRationalBezierCurve.h"
#include "IFC2X3/IfcTrimmedCurve.h"

#include "ifcgeom/core/types.h"

namespace ifcgeom {

std::vector<Point_3> composite_crv(IFC2X3::IfcCompositeCurve const* crv);
std::vector<Point_3> composite_crv_2d(IFC2X3::Ifc2DCompositeCurve const* crv);
std::vector<Point_3> polyline(IFC2X3::IfcPolyline const* crv);
std::vector<Point_3> trimmed_crv(IFC2X3::IfcTrimmedCurve const* crv);
std::vector<Point_3> bezier_crv(IFC2X3::IfcBezierCurve const* crv);
std::vector<Point_3> rational_bezier_crv(
    IFC2X3::IfcRationalBezierCurve const* crv);

std::vector<Point_3> circle(IFC2X3::IfcCircle const* crv);
std::vector<Point_3> ellipse(IFC2X3::IfcEllipse const* crv);

std::vector<Point_3> line(IFC2X3::IfcLine const* crv);

std::vector<Point_3> offset_crv_2d(IFC2X3::IfcOffsetCurve2D const* crv);
std::vector<Point_3> offset_crv_3d(IFC2X3::IfcOffsetCurve3D const* crv);

std::vector<Point_3> curve_handler(IFC2X3::IfcCurve* item);

}  // namespace ifcgeom
