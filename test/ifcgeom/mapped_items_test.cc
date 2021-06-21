#include "doctest/doctest.h"

#include <iostream>

#include "IFC2X3/IfcMappedItem.h"
#include "IFC2X3/IfcProduct.h"
#include "IFC2X3/IfcRepresentation.h"

#include "ifcgeom/core/context.h"
#include "ifcgeom/core/filters.h"

TEST_CASE("find mapped items") {
  auto path = "../resources/BES-SAN-OH-GR-U2-4100B-000-H5-a_DD05.ifc";
  auto ctx = ifcgeom::context{path};
  REQUIRE(!ctx.model_.entity_mem_.empty());

  auto p = ifcgeom::get_entity_by_id<IFC2X3::IfcProduct>(ctx.model_, 325);
  REQUIRE(p.has_value());
  REQUIRE(p.value()->Representation_.has_value());
  auto repr = p.value()->Representation_.value();

  for (auto const r : repr->Representations_) {
    for (auto const item : r->Items_) {
      std::cout << item->id_ << "\n";
    }
  }
}