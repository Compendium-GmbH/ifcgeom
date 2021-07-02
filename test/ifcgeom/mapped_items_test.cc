#include "doctest/doctest.h"

#include <iostream>

#include "IFC2X3/IfcBuildingElementProxy.h"
#include "IFC2X3/IfcCartesianPoint.h"
#include "IFC2X3/IfcCartesianTransformationOperator3D.h"
#include "IFC2X3/IfcCartesianTransformationOperator3DnonUniform.h"
#include "IFC2X3/IfcMappedItem.h"
#include "IFC2X3/IfcProduct.h"
#include "IFC2X3/parser.h"

#include "ifcgeom/core/context.h"
#include "ifcgeom/core/filters.h"
#include "ifcgeom/core/geom_hash.h"
#include "ifcgeom/core/render.h"
#include "ifcgeom/core/types.h"
#include "ifcgeom/core/utilities.h"
#include "ifcgeom/core/xform.h"

TEST_CASE("gather vertices of mapped items") {
  auto path = "../resources/mapped_repr.ifc";
  auto ctx = ifcgeom::context{path};
  REQUIRE(!ctx.model_.entity_mem_.empty());

  auto p = ifcgeom::get_entity_by_id<IFC2X3::IfcProduct>(ctx.model_, 1000);
  REQUIRE(p.has_value());
  REQUIRE(p.value()->Representation_.has_value());

  auto vertices = ifcgeom::gather_product_vertices(ctx, p.value());

  auto centroid = ifcgeom::approx_centroid(vertices);
  CHECK(centroid.x() == doctest::Approx(1500));
  CHECK(centroid.y() == doctest::Approx(500));
  CHECK(centroid.z() == doctest::Approx(1000));
}

TEST_CASE("cartesian transformation operator") {
  constexpr auto const input = R"(
#1 = IFCCARTESIANPOINT((3.000000, 1.000000, 1.000000));
#2 = IFCDIRECTION((0.000000, -1.000000, 0.000000));
#3 = IFCDIRECTION((1.000000, 0.000000, 0.000000));
#4 = IFCCARTESIANPOINT((1.000000, 2.500000, 0.000000));
#5 = IFCCARTESIANTRANSFORMATIONOPERATOR3D(#2, #3, #4, .5, $);)";

  auto const model = IFC2X3::parse(input);
  REQUIRE(!model.entity_mem_.empty());
  auto const p1 =
      ifcgeom::get_entity_by_id<IFC2X3::IfcCartesianPoint>(model, 1);
  REQUIRE(p1.has_value());
  auto const trans_op =
      ifcgeom::get_entity_by_id<IFC2X3::IfcCartesianTransformationOperator>(
          model, 5);
  REQUIRE(trans_op.has_value());
  auto const t = ifcgeom::h_transformation(trans_op.value());
  auto const p2 = t.transform(ifcgeom::to_point_3(p1.value()));
  CHECK(p2.x() == 1.5);
  CHECK(p2.y() == 1.0);
  CHECK(p2.z() == 0.5);
}

TEST_CASE("cartesian transformation operator non-uniform") {
  constexpr auto const input = R"(
#318 = IFCCARTESIANPOINT((1000., 1000., 1000.));
#1033 = IFCCARTESIANPOINT((1000.,0.,0.));
#904= IFCDIRECTION((0.,0.,1.));
#908= IFCDIRECTION((1.,1.,0.));
#909= IFCDIRECTION((-1.,1.,0.));
#1032= IFCCARTESIANTRANSFORMATIONOPERATOR3DNONUNIFORM(#908,#909,#1033,0.5,#904,0.5,1.5);)";

  auto const model = IFC2X3::parse(input);
  REQUIRE(!model.entity_mem_.empty());
  auto const p1 =
      ifcgeom::get_entity_by_id<IFC2X3::IfcCartesianPoint>(model, 318);
  REQUIRE(p1.has_value());
  auto const trans_op = ifcgeom::get_entity_by_id<
      IFC2X3::IfcCartesianTransformationOperator3DnonUniform>(model, 1032);
  REQUIRE(trans_op.has_value());
  auto const ct = ifcgeom::h_transformation(trans_op.value());
  auto const p2 = ct.transform(ifcgeom::to_point_3(p1.value()));
  CHECK(p2.x() == doctest::Approx(1000));
  CHECK(p2.y() == doctest::Approx(707.1067811865));
  CHECK(p2.z() == doctest::Approx(1500));
}

TEST_CASE("mapping source transformation") {
  auto path = "../resources/mapped_repr.ifc";
  auto ctx = ifcgeom::context{path};
  REQUIRE(!ctx.model_.entity_mem_.empty());
  auto const mapped_obj =
      ifcgeom::get_entity_by_id<IFC2X3::IfcBuildingElementProxy>(ctx.model_,
                                                                 1000);
  REQUIRE(mapped_obj.has_value());
  REQUIRE(mapped_obj.value()->Representation_.has_value());

  auto const local_plcmt = dynamic_cast<IFC2X3::IfcLocalPlacement const*>(
      mapped_obj.value()->ObjectPlacement_.value());
  auto local_transformation = ifcgeom::h_transformation(local_plcmt);
  auto p = ifcgeom::Vector_3{0, 0, 0};
  CHECK(p.transform(local_transformation) == p);

  auto const mapped_item =
      dynamic_cast<IFC2X3::IfcMappedItem const*>(mapped_obj.value()
                                                     ->Representation_.value()
                                                     ->Representations_.at(0)
                                                     ->Items_.at(0));

  auto const mapping_origin = mapped_item->MappingSource_->MappingOrigin_;

  auto const src_vertices = ifcgeom::gather_vertices(
      mapped_item->MappingSource_->MappedRepresentation_);

  CHECK(src_vertices.at(2).x() == doctest::Approx(500.0));
  CHECK(src_vertices.at(2).y() == doctest::Approx(500.0));
  CHECK(src_vertices.at(2).z() == doctest::Approx(.0));

  CHECK(src_vertices.at(5).x() == doctest::Approx(500.0));
  CHECK(src_vertices.at(5).y() == doctest::Approx(-500.0));
  CHECK(src_vertices.at(5).z() == doctest::Approx(2000.0));

  auto transformed_vertices = ifcgeom::cartesian_transformation(
      mapped_item->MappingTarget_, src_vertices);

  CHECK(transformed_vertices.at(0).x() == doctest::Approx(.0));
  CHECK(transformed_vertices.at(0).y() == doctest::Approx(-353.55339));
  CHECK(transformed_vertices.at(0).z() == doctest::Approx(.0));

  CHECK(transformed_vertices.at(5).x() == doctest::Approx(353.55339));
  CHECK(transformed_vertices.at(5).y() == doctest::Approx(.0));
  CHECK(transformed_vertices.at(5).z() == doctest::Approx(2000.0));

  auto centroid = ifcgeom::approx_centroid(transformed_vertices);
  CHECK(centroid.x() == doctest::Approx(0));
  CHECK(centroid.y() == doctest::Approx(0));
  CHECK(centroid.z() == doctest::Approx(1000));
}

TEST_CASE("compare geometries") {
  auto path = "../resources/Wand_ArchiCad.ifc";
  auto ctx = ifcgeom::context{path};
  REQUIRE(!ctx.model_.entity_mem_.empty());

  auto p = ifcgeom::get_entity_by_guid<IFC2X3::IfcProduct>(
      ctx.model_, "2u5_tm$m5AcRsm_0pKv8Pt");
  REQUIRE(p.has_value());
  REQUIRE(p.value()->Representation_.has_value());

  auto vertices = ifcgeom::gather_product_vertices(ctx, p.value());

  auto path2 = "../resources/Wand_ArchiCad_BRep.ifc";
  auto ctx2 = ifcgeom::context{path2};
  REQUIRE(!ctx2.model_.entity_mem_.empty());

  auto p2 = ifcgeom::get_entity_by_guid<IFC2X3::IfcProduct>(
      ctx2.model_, "2u5_tm$m5AcRsm_0pKv8Pt");
  REQUIRE(p2.has_value());
  REQUIRE(p2.value()->Representation_.has_value());

  auto vertices2 = ifcgeom::gather_product_vertices(ctx2, p2.value());

  CHECK(ifcgeom::geom_hash(vertices) == ifcgeom::geom_hash(vertices2));
}
