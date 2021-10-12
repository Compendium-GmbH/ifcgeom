#include "doctest/doctest.h"

#include <iostream>

#include "ifcgeom/core/context.h"
#include "ifcgeom/core/filters.h"
#include "ifcgeom/core/geom_hash.h"
#include "ifcgeom/core/render.h"

TEST_CASE("geometry identification") {
  auto path = "../resources/mapped_repr.ifc";
  auto ctx = ifcgeom::context{path};
  REQUIRE(!ctx.model_.entity_mem_.empty());

  auto p = ifcgeom::get_entity_by_id<IFC2X3::IfcProduct>(ctx.model_, 1000);
  REQUIRE(p.has_value());
  REQUIRE(p.value()->Representation_.has_value());

  auto vertices = ifcgeom::gather_product_vertices(ctx, p.value());
  for (auto const v : vertices) {
    std::cout << v << "\n";
  }
  std::cout << ifcgeom::geom_hash<true>(vertices) << std::endl;
}

TEST_CASE("geometry matching 1") {
  auto path = "../resources/Wand_ArchiCad.ifc";
  auto ctx = ifcgeom::context{path};
  REQUIRE(!ctx.model_.entity_mem_.empty());

  for (auto const p :
       ifcgeom::filter_entities<IFC2X3::IfcProduct>(ctx.model_)) {
    if (!p->Representation_.has_value()) {
      continue;
    }

    auto vertices = ifcgeom::gather_product_vertices(ctx, p);
    std::cout << ifcgeom::geom_hash(vertices) << std::endl;
  }
}

TEST_CASE("geometry matching 2") {
  auto path = "../resources/BES-SAN-OH-GR-U2-4100B-000-H5-a_DD05.ifc";
  auto ctx = ifcgeom::context{path};
  REQUIRE(!ctx.model_.entity_mem_.empty());

  auto map = std::unordered_map<double, std::string>{};
  auto collision_count = 0U;
  auto geometry_count = 0U;

  for (auto const p :
       ifcgeom::filter_entities<IFC2X3::IfcProduct>(ctx.model_)) {
    if (!p->Representation_.has_value()) {
      continue;
    }

    ++geometry_count;

    auto vertices = ifcgeom::gather_product_vertices(ctx, p);
    auto hash = ifcgeom::geom_hash(vertices);

    if (map.find(hash) == map.end()) {
      map.insert({hash, p->GlobalId_});
    } else {
      ++collision_count;
    }
  }

  std::cout << "geometry_count" << geometry_count << "\n";
  std::cout << "collision_count" << collision_count << "\n";
}
