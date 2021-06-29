#include "IFC2X3/IfcDirection.h"

#include "doctest/doctest.h"

#include "ifcgeom/core/context.h"
#include "ifcgeom/geometric_repr_item/solid_model.h"

TEST_CASE("Revolved Area Test") {
  // Input create IFC2X3::IfcRevolvedAreaSolid
  IFC2X3::IfcRevolvedAreaSolid revolvedArea;
  // TODO: create vertices and put them in Swept_Area
  revolvedArea.SweptArea_;

  revolvedArea.Angle_ = 90.0;

  IFC2X3::IfcAxis1Placement a1p;
  IFC2X3::IfcDirection direction;
  direction.DirectionRatios_.push_back(0);
  direction.DirectionRatios_.push_back(1);
  direction.DirectionRatios_.push_back(0);
  a1p.Axis_ = std::optional<IFC2X3::IfcDirection*>{&direction};
  revolvedArea.Axis_ = &a1p;

  // Ground truth  create std::vector<Point_3>
  // TODO: calculate the vertices manually
  std::vector<ifcgeom::Point_3> vertices_ground_truth;

  // Output from Revolved Area
  std::vector<ifcgeom::Point_3> vertices_out =
      ifcgeom::revolved_area(&revolvedArea);
  // Test  output against ground truth
  // TODO: check for differences in output and ground truth
  // TODO: check for the right amount of vertices
}
