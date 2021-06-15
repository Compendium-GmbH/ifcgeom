#pragma once

#include <type_traits>

#include "utl/overloaded.h"

#include "step/root_entity.h"

namespace ifcgeom {

template <typename Parent, typename Fn>
auto match(Parent&& p, Fn&& f) {
  if (auto const casted = dynamic_cast<utl::first_argument<Fn>>(p);
      casted != nullptr) {
    return f(casted);
  } else {
    auto root = reinterpret_cast<step::root_entity*>(p);
    add_to_map(render_err_log_, std::string{root->name()}, __func__);
    return std::vector<Point_3>{};
    // throw std::runtime_error{"no matching class found"};
  }
}

template <typename Parent, typename Fn, typename... RestFn>
auto match(Parent&& p, Fn&& f, RestFn&&... rest_f) {
  if (auto const casted = dynamic_cast<utl::first_argument<Fn>>(p);
      casted != nullptr) {
    return f(casted);
  } else {
    return match(std::forward<Parent>(p), std::forward<RestFn>(rest_f)...);
  }
}

}  // namespace ifcgeom