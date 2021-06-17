#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

#include "IFC2X3/IfcProduct.h"

#include "ifcgeom/tools/filters.h"

#include "ifcgeom/core/context.h"

namespace ifcgeom {

inline void iterate_repr(IFC2X3::IfcProductRepresentation const* prod) {
  for (auto const repr : prod->Representations_) {
    render_err_log.emplace_back(repr->name());
    for (auto const item : repr->Items_) {
      render_err_log.emplace_back(item->name());
    }
  }
}

void list_geometry_types(std::string const& path) {
  auto ctx = ifcgeom::context{path};
  auto products = ifcgeom::filter_entities<IFC2X3::IfcProduct>(ctx.model_);
  for (auto const p : products) {
    if (!p->Representation_.has_value()) {
      continue;
    }
    iterate_repr(p->Representation_.value());
    auto shapes = ifcgeom::repr_by_guid(ctx.element_part_map_, p->GlobalId_);
    for (auto const repr : shapes) {
      iterate_repr(repr);
    }
  }
}

template <typename T>
std::vector<T> unique_values(std::vector<T>& input_vec) {
  std::vector<T> uniques(input_vec.size());
  typename std::vector<T>::iterator it;
  it = std::unique_copy(input_vec.begin(), input_vec.end(), uniques.begin());

  std::sort(uniques.begin(), it);
  it = std::unique_copy(uniques.begin(), it, uniques.begin());
  uniques.resize(static_cast<unsigned>(std::distance(uniques.begin(), it)));

  return uniques;
}

template <typename T>
std::vector<unsigned> count_unique_values(std::vector<T>& input_vec) {
  std::vector<T> uniques = unique_values<T>(input_vec);
  std::vector<unsigned> counts(uniques.size());

  for (unsigned i = 0; i < counts.size(); ++i) {
    auto count = std::count(input_vec.begin(), input_vec.end(), uniques[i]);
    counts[i] = static_cast<unsigned>(count);
  }

  return counts;
}

template <typename T>
void print_distribution(std::vector<T>& input_vec) {
  auto scan_result = ifcgeom::unique_values(input_vec);
  auto counts = ifcgeom::count_unique_values(input_vec);

  for (unsigned i = 0; i < scan_result.size(); ++i) {
    std::cout << scan_result.at(i) << " x" << counts.at(i) << std::endl;
  }
}

}  // namespace ifcgeom
