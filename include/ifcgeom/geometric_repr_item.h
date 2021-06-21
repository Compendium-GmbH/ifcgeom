#pragma once

#include <vector>

#include "IFC2X3/IfcBoundingBox.h"
#include "IFC2X3/IfcCompositeCurveSegment.h"
#include "IFC2X3/IfcDirection.h"
#include "IFC2X3/IfcFaceBasedSurfaceModel.h"
#include "IFC2X3/IfcSectionedSpine.h"
#include "IFC2X3/IfcShell.h"
#include "IFC2X3/IfcShellBasedSurfaceModel.h"
#include "IFC2X3/IfcVector.h"

#include "ifcgeom/core/types.h"

namespace ifcgeom {

std::vector<Point_3> direction(IFC2X3::IfcDirection const* dir);
std::vector<Point_3> vector(IFC2X3::IfcVector const* v);
std::vector<Point_3> bounding_box(IFC2X3::IfcBoundingBox const* bbox);
std::vector<Point_3> sectioned_spine(IFC2X3::IfcSectionedSpine const* spine);

std::vector<Point_3> face_based_srf_model(
    IFC2X3::IfcFaceBasedSurfaceModel const* srf);
std::vector<Point_3> shell_based_srf_model(
    IFC2X3::IfcShellBasedSurfaceModel const* srf);

std::vector<Point_3> geometric_repr_item_handler(
    IFC2X3::IfcGeometricRepresentationItem* item);

}  // namespace ifcgeom
