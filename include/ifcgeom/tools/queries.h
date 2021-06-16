#pragma once

#include <fstream>

#include "utl/to_vec.h"

#include "cista/containers/hash_map.h"

#include "IFC2X3/IfcMaterial.h"
#include "IFC2X3/IfcProduct.h"
#include "IFC2X3/IfcProductRepresentation.h"
#include "IFC2X3/IfcProperty.h"
#include "IFC2X3/IfcPropertySet.h"
#include "IFC2X3/IfcPropertySingleValue.h"
#include "IFC2X3/IfcRelAggregates.h"
#include "IFC2X3/IfcRelDefinesByProperties.h"
#include "IFC2X3/IfcRelDefinesByType.h"
#include "IFC2X3/IfcRepresentationItem.h"
#include "IFC2X3/IfcTypeObject.h"
#include "IFC2X3/parser.h"

#include "ifcgeom/tools/filters.h"

namespace ifcgeom {

using building_elements = std::vector<IFC2X3::IfcBuildingElementPart*>;
using element_part_map = cista::raw::hash_map<std::string, building_elements>;

inline std::vector<IFC2X3::IfcPropertySet*> psets_by_product(
    step::model& model, IFC2X3::IfcProduct const& product) {
  std::vector<IFC2X3::IfcPropertySet*> p_sets;
  for (auto const rel_def :
       filter_entities<IFC2X3::IfcRelDefinesByProperties>(model)) {
    auto const p_set = dynamic_cast<IFC2X3::IfcPropertySet*>(
        rel_def->RelatingPropertyDefinition_);
    if (p_set == nullptr) {
      continue;
    }

    for (auto const& p : rel_def->RelatedObjects_) {
      if (p != nullptr && p->GlobalId_ == product.GlobalId_) {
        p_sets.push_back(p_set);
      }
    }
  }
  return p_sets;
}

inline std::optional<IFC2X3::IfcTypeObject*> type_by_product(
    step::model& model, IFC2X3::IfcProduct const& product) {
  for (auto const rel_type :
       filter_entities<IFC2X3::IfcRelDefinesByType>(model)) {
    auto const type =
        dynamic_cast<IFC2X3::IfcTypeObject*>(rel_type->RelatingType_);
    if (type == nullptr) {
      continue;
    }

    for (auto const& p : rel_type->RelatedObjects_) {
      if (p != nullptr && p->GlobalId_ == product.GlobalId_) {
        return type;
      }
    }
  }
  return std::nullopt;
}

inline std::vector<IFC2X3::IfcPropertySet*> psets_by_type(
    IFC2X3::IfcTypeObject const& type) {
  if (!type.HasPropertySets_.has_value()) {
    return {};
  }

  return utl::to_vec(*type.HasPropertySets_, [](auto&& set_definition) {
    auto const p_set = dynamic_cast<IFC2X3::IfcPropertySet*>(set_definition);
    utl::verify(p_set != nullptr, "bad dynamic cast");
    return p_set;
  });
}

inline std::vector<IFC2X3::IfcPropertySingleValue*> properties_by_pset(
    IFC2X3::IfcPropertySet const& p_set) {
  return utl::to_vec(p_set.HasProperties_, [](auto&& property) {
    auto const value = dynamic_cast<IFC2X3::IfcPropertySingleValue*>(property);
    utl::verify(value != nullptr, "bad dynamic cast");
    return value;
  });
}

inline std::vector<IFC2X3::IfcProductRepresentation*> repr_by_guid(
    element_part_map& map, std::string const& guid) {
  std::vector<IFC2X3::IfcProductRepresentation*> representations;
  if (map.find(guid) != map.end()) {
    for (auto const elem : map.at(guid)) {
      if (elem->Representation_.has_value()) {
        representations.push_back(elem->Representation_.value());
      }
    }
  }
  return representations;
}

inline element_part_map create_element_part_map(step::model& model) {
  element_part_map map;
  for (auto const rel_aggr : filter_entities<IFC2X3::IfcRelAggregates>(model)) {
    auto const id = rel_aggr->RelatingObject_->GlobalId_;
    std::vector<IFC2X3::IfcBuildingElementPart*> elements;
    for (auto const obj : rel_aggr->RelatedObjects_) {
      auto const elem = reinterpret_cast<IFC2X3::IfcBuildingElementPart*>(obj);
      if (elem != nullptr) {
        elements.push_back(elem);
      }
    }
    map.emplace(id, elements);
  }
  return map;
}

}  // namespace ifcgeom
