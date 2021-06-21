#include "doctest/doctest.h"

#include <iostream>

#include "IFC2X3/IfcMappedItem.h"
#include "IFC2X3/IfcProduct.h"
#include "IFC2X3/IfcRepresentation.h"

#include "ifcgeom/core/context.h"
#include "ifcgeom/core/filters.h"

TEST_CASE("gather vertices, mapped items") {
  auto path = "../resources/BES-SAN-OH-GR-U2-4100B-000-H5-a_DD05.ifc";
  auto ctx = ifcgeom::context{path};
  REQUIRE(!ctx.model_.entity_mem_.empty());

  auto p = ifcgeom::get_entity_by_id<IFC2X3::IfcProduct>(ctx.model_, 325);
  REQUIRE(p.has_value());
  REQUIRE(p.value()->Representation_.has_value());

  auto vertices = ifcgeom::gather_product_vertices(ctx, p.value());
}

TEST_CASE("transform mapped item vertices") {}

// auto m_src = mapped_item->MappingSource_;  // IFCREPRESENTATIONMAP
////        auto m_target = mapped_item->MappingTarget_; //
////        IFCCARTESIANTRANSFORMATIONOPERATOR3D
//
// auto mapped_repr = m_src->MappedRepresentation_;  // IfcRepresentation
////        auto const m_origin = m_src->MappingOrigin_; // axis2placement
// for (auto const i : mapped_repr->Items_) {
// std::cout << i->id_ << "\n";
// std::cout << i->name() << "\n";
//}