#include "doctest/doctest.h"

#include "ifcgeom/core/context.h"
#include "ifcgeom/core/filters.h"
#include "ifcgeom/core/geom_hash.h"
#include "ifcgeom/core/render.h"
#include "ifcgeom/core/types.h"

#include "ifcgeom/geometric_repr_item/solid_model.h"

TEST_CASE("product coordinate transformation") {
  auto path = "../resources/Wand_ArchiCad.ifc";
  auto ctx = ifcgeom::context{path};
  REQUIRE(!ctx.model_.entity_mem_.empty());

  auto p = ifcgeom::get_entity_by_id<IFC2X3::IfcProduct>(ctx.model_, 186);
  REQUIRE(p.has_value());

  auto local_placement =
      ifcgeom::get_entity_by_id<IFC2X3::IfcLocalPlacement>(ctx.model_, 134);
  REQUIRE(local_placement.has_value());
  auto const xform = ifcgeom::h_transformation(local_placement.value());

  auto extr_area =
      ifcgeom::get_entity_by_id<IFC2X3::IfcExtrudedAreaSolid>(ctx.model_, 158);
  REQUIRE(extr_area.has_value());
  auto vertices = ifcgeom::extruded_area(extr_area.value());

  auto const v1 = vertices.at(0).transform(xform);
  auto const local_origin = ifcgeom::Point_3{1140.22108844, 18007.8640078, 0.};
  CHECK(v1.x() - local_origin.x() == doctest::Approx(50));
  CHECK(v1.y() - local_origin.y() == doctest::Approx(-50));
  CHECK(v1.z() - local_origin.z() == doctest::Approx(0));
}

//