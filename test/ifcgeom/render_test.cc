#include "doctest/doctest.h"

#include "IFC2X3/IfcProduct.h"

#include "ifcgeom/core/analysis.h"
#include "ifcgeom/core/context.h"
#include "ifcgeom/core/render.h"

#include "ifcgeom/tools/filters.h"

TEST_CASE("Render Test") {
  auto path = "../resources/brep/HZG-OH-ZP-U1-4200M-004-H5-b_DD04.ifc";
  auto ctx = ifcgeom::context{path};
  REQUIRE(!ctx.model_.entity_mem_.empty());

  auto e = ifcgeom::filter_entities<IFC2X3::IfcProduct>(ctx.model_);
  for (auto const p : e) {
    auto const geo = ifcgeom::gather_product_vertices(ctx, p);
  }

  ifcgeom::print(ifcgeom::render_err_log_);
}