#pragma once

#include "IFC2X3/IfcAxis1Placement.h"
#include "IFC2X3/IfcAxis2Placement2D.h"
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

#include "ifcgeom/core/types.h"

namespace ifcgeom {

std::vector<Point_3> faceted_brep(IFC2X3::IfcFacetedBrep const* brep);
std::vector<Point_3> faceted_brep_with_voids(
    IFC2X3::IfcFacetedBrepWithVoids const* brep);

std::vector<Point_3> extruded_area(IFC2X3::IfcExtrudedAreaSolid const* ext);
std::vector<Point_3> revolved_area(
    IFC2X3::IfcRevolvedAreaSolid const* revolved);
std::vector<Point_3> surface_curve(
    IFC2X3::IfcSurfaceCurveSweptAreaSolid const* crv);

std::vector<Point_3> csg_solid(IFC2X3::IfcCsgSolid const* csg);

std::vector<Point_3> swept_disk(IFC2X3::IfcSweptDiskSolid const* swept);

std::vector<Point_3> solid_model_handler(IFC2X3::IfcSolidModel* item);

}  // namespace ifcgeom
