#pragma once

#include <optional>
#include <string>

#include "step/model.h"

#include "utl/pipes.h"

namespace ifcgeom {

template <typename T>
std::optional<T*> get_entity_by_id(step::model const& m, unsigned const& id) {
  for (auto const& ptr : m.entity_mem_) {
    auto const casted = dynamic_cast<T*>(ptr.get());
    if (casted != nullptr && casted->id_.id_ == id) {
      return casted;
    }
  }
  return std::nullopt;
}

template <typename T>
std::optional<T*> get_entity_by_guid(step::model const& m,
                                     std::string const& guid) {
  for (auto const& ptr : m.entity_mem_) {
    auto const casted = dynamic_cast<T*>(ptr.get());
    if (casted != nullptr && casted->GlobalId_ == guid) {
      return casted;
    }
  }
  return std::nullopt;
}

template <typename T>
auto filter_entities(step::model const& m) {
  return utl::all(m.entity_mem_) |
         utl::transform([](auto&& e) { return dynamic_cast<T*>(e.get()); }) |
         utl::remove_if([](auto&& e) { return e == nullptr; }) |
         utl::iterable();
}

}  // namespace ifctools
