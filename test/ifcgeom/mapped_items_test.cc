#include "doctest/doctest.h"

#include <iostream>
#include <vector>

#include "IFC2X3/IfcBuildingElementProxy.h"
#include "IFC2X3/IfcCartesianPoint.h"
#include "IFC2X3/IfcCartesianTransformationOperator3D.h"
#include "IFC2X3/IfcCartesianTransformationOperator3DnonUniform.h"
#include "IFC2X3/IfcMappedItem.h"
#include "IFC2X3/IfcProduct.h"
#include "IFC2X3/IfcRepresentation.h"
#include "IFC2X3/IfcShapeRepresentation.h"
#include "IFC2X3/parser.h"

#include "ifcgeom/core/context.h"
#include "ifcgeom/core/filters.h"
#include "ifcgeom/core/render.h"
#include "ifcgeom/core/types.h"
#include "ifcgeom/core/utilities.h"
#include "ifcgeom/core/xform.h"

TEST_CASE("gather vertices, mapped items") {
  auto path = "../resources/BES-SAN-OH-GR-U2-4100B-000-H5-a_DD05.ifc";
  auto ctx = ifcgeom::context{path};
  REQUIRE(!ctx.model_.entity_mem_.empty());

  auto p = ifcgeom::get_entity_by_id<IFC2X3::IfcProduct>(ctx.model_, 325);
  REQUIRE(p.has_value());
  REQUIRE(p.value()->Representation_.has_value());

  auto vertices = ifcgeom::gather_product_vertices(ctx, p.value());
}

#include "IFC2X3/IfcRepresentationItem.h"

TEST_CASE("transform mapped item vertices") {
  auto path = "../resources/BES-SAN-OH-GR-U2-4100B-000-H5-a_DD05.ifc";
  auto ctx = ifcgeom::context{path};
  REQUIRE(!ctx.model_.entity_mem_.empty());

  auto p = ifcgeom::get_entity_by_id<IFC2X3::IfcProduct>(ctx.model_, 325);
  REQUIRE(p.has_value());
  REQUIRE(p.value()->Representation_.has_value());

  for (auto const repr : p.value()->Representation_.value()->Representations_) {
    for (auto const item : repr->Items_) {
      auto const mapped_item = dynamic_cast<IFC2X3::IfcMappedItem*>(item);

      // MappingSource 	 :  	IfcRepresentationMap;
      //      auto mapped_repr = mapped_item->MappingSource_
      //                             ->MappedRepresentation_;  //
      //                             IfcRepresentation
      //      auto const mapping_origin =
      //          mapped_item->MappingSource_->MappingOrigin_;  //
      //          axis2placement

      // MappingTarget 	 :  	IfcCartesianTransformationOperator;
      auto const m_target = mapped_item->MappingTarget_;

      auto const pts = ifcgeom::gather_product_vertices(ctx, p.value());
      auto transformed_pts = std::vector<ifcgeom::Point_3>{};
      transformed_pts.resize(pts.size());
      for (auto const v : pts) {
        auto const t = ifcgeom::cartesian_transformation(m_target);
        transformed_pts.emplace_back(t.transform(v));
      }
    }
  }
}

TEST_CASE("cartesian transformation operator") {
  constexpr auto const input = R"(
#318 = IFCCARTESIANPOINT((3.000000, 1.000000, 0.000000));
#319 = IFCDIRECTION((1.000000, 0.000000, 0.000000));
#320 = IFCDIRECTION((0.000000, -1.000000, 0.000000));
#323 = IFCCARTESIANPOINT((3.000000, -2.000000, 0.000000));
#322 = IFCCARTESIANTRANSFORMATIONOPERATOR3D(#320, #319, #323, .5, $);)";

  auto const model = IFC2X3::parse(input);
  REQUIRE(!model.entity_mem_.empty());
  auto const p1 =
      ifcgeom::get_entity_by_id<IFC2X3::IfcCartesianPoint>(model, 318);
  REQUIRE(p1.has_value());
  auto const trans_op =
      ifcgeom::get_entity_by_id<IFC2X3::IfcCartesianTransformationOperator>(
          model, 322);
  REQUIRE(trans_op.has_value());
  auto const t = ifcgeom::cartesian_transformation(trans_op.value());
  auto const p2 = t.transform(ifcgeom::to_point_3(p1.value()));
  CHECK(p2.x() == 2);
  CHECK(p2.y() == -2.5);
  CHECK(p2.z() == 0);
}

TEST_CASE("cartesian transformation operator non-uniform") {
  constexpr auto const input = R"(
#318 = IFCCARTESIANPOINT((1000., 1000., 1000.));
#1033 = IFCCARTESIANPOINT((1000.,0.,0.));
#904= IFCDIRECTION((0.,0.,1.));
#908= IFCDIRECTION((1.,1.,0.));
#909= IFCDIRECTION((-1.,1.,0.));
#1032= IFCCARTESIANTRANSFORMATIONOPERATOR3DNONUNIFORM(#908,#909,#1033,0.5,#904,0.5,1.);)";

  auto const model = IFC2X3::parse(input);
  REQUIRE(!model.entity_mem_.empty());
  auto const p1 =
      ifcgeom::get_entity_by_id<IFC2X3::IfcCartesianPoint>(model, 318);
  REQUIRE(p1.has_value());
  auto const trans_op = ifcgeom::get_entity_by_id<
      IFC2X3::IfcCartesianTransformationOperator3DnonUniform>(model, 1032);
  REQUIRE(trans_op.has_value());
  auto const t = ifcgeom::cartesian_transformation(trans_op.value());
  auto const p2 = t.transform(ifcgeom::to_point_3(p1.value()));
  CHECK(p2.x() == doctest::Approx(500));
  CHECK(p2.y() == doctest::Approx(707.1067811865));
  CHECK(p2.z() == doctest::Approx(1000));
}

TEST_CASE("mapping") {
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
  auto local_transformation = ifcgeom::h_transform(local_plcmt);

  auto shape_repr = dynamic_cast<IFC2X3::IfcShapeRepresentation const*>(
      mapped_obj.value()->Representation_.value()->Representations_.at(0));
  std::cout << shape_repr->name() << std::endl;
  //  ifcgeom::read_shape_representation(shape_repr);

  for (auto const repr :
       mapped_obj.value()->Representation_.value()->Representations_) {
    for (auto const item : repr->Items_) {
      auto const mapped_item = dynamic_cast<IFC2X3::IfcMappedItem*>(item);

      //       ------------------------------------------------------------------
      //       MappingSource 	 :  	IfcRepresentationMap;
      //       ------------------------------------------------------------------
      auto const mapping_origin = mapped_item->MappingSource_->MappingOrigin_;
      auto local_plcmt_src = ifcgeom::matrix(
          std::get<IFC2X3::IfcAxis2Placement3D*>(mapping_origin.data_));

      // ------------------------------------------------------------------
      // MappingTarget 	 :  	IfcCartesianTransformationOperator;
      // ------------------------------------------------------------------
      //      auto const mapping_transf =
      //      ifcgeom::cartesian_transformation_non_uniform(
      //          dynamic_cast<
      //              IFC2X3::IfcCartesianTransformationOperator3DnonUniform
      //              const*>( mapped_item->MappingTarget_));
    }
  }
}
