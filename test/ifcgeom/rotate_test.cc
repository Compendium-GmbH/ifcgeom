
#include "doctest/doctest.h"
#include "ifcgeom/core/context.h"
#include "ifcgeom/core/utilities.h"

TEST_CASE("Rotate Test") {
  // Create Point_3
  ifcgeom::Point_3 point_in{2, 2, 2};
  // Create IFC2X3::IfcAxis1Placement with unit up vector
  IFC2X3::IfcAxis1Placement a1p;
  IFC2X3::IfcDirection direction;
  direction.DirectionRatios_.push_back(0);
  direction.DirectionRatios_.push_back(1);
  direction.DirectionRatios_.push_back(0);
  a1p.Axis_ = std::optional<IFC2X3::IfcDirection*>{&direction};

  // Test rotate
  ifcgeom::Point_3 point_out = ifcgeom::rotate(point_in, &a1p, 180.0);
  ifcgeom::Point_3 point_ground_truth{-2, 2, -2};
  CHECK(std::abs(point_ground_truth.x() - point_out.x()) <=
        std::numeric_limits<float>::epsilon());
  CHECK(std::abs(point_ground_truth.y() - point_out.y()) <=
        std::numeric_limits<float>::epsilon());
  CHECK(std::abs(point_ground_truth.z() - point_out.z()) <=
        std::numeric_limits<float>::epsilon());
}