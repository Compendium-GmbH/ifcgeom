#pragma once
#include <string>
#include <vector>

#include "context.h"
#include "io.h"

#include "ifctools/filters.h"
#include "ifctools/queries.h"

#include "IFC2X3/IfcRepresentationItem.h"

#include "cista/containers/hash_map.h"

namespace ifcgeom {

inline void add_to_map(type_map& map, std::string const& key,
                       std::string const& func = "") {
  try {
    ++map.at(key)->count;
  } catch (...) {
    map.emplace(key, new repr_type);
    map.at(key)->func = func;
  }
}

inline void iterate_repr(type_map& map,
                         IFC2X3::IfcProductRepresentation const* prod) {
  for (auto const repr : prod->Representations_) {
    add_to_map(map, std::string{repr->name()});
    if (repr->RepresentationType_.has_value()) {
      auto& m2 = map.at(repr->name())->children;
      add_to_map(m2, repr->RepresentationType_.value());
      for (auto const item : repr->Items_) {
        auto& m3 = m2.at(repr->RepresentationType_.value())->children;
        add_to_map(m3, std::string{item->name()});
      }
    }
  }
}

inline void map_geometry_types(context& ctx, type_map& map) {
  auto e = ifctools::filter_entities<IFC2X3::IfcProduct>(ctx.model_);
  for (auto const product : e) {
    // Product Representations
    if (product->Representation_.has_value()) {
      iterate_repr(map, product->Representation_.value());
    }
    // Aggregated Representations
    auto s = ifctools::repr_by_guid(ctx.element_part_map_, product->GlobalId_);
    for (auto const repr : s) {
      iterate_repr(map, repr);
    }
  }
}

inline void print(type_map const& map) {
  std::function<void(type_map const& sub_map, size_t i)> print;
  print = [&](type_map const& sub_map, size_t count) {
    if (!sub_map.empty()) {
      for (auto const pair : sub_map) {
        std::string tab;
        for (int i = 0; i < count; ++i) {
          tab += "\t";
        }
        std::cout << tab << pair.first << " [" << pair.second->func << "]"
                  << " x" << pair.second->count << std::endl;
        print(pair.second->children, count + 1);
      }
    }
  };
  print(map, 0);
}

}  // namespace ifcgeom
