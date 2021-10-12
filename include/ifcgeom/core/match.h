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
    return std::vector<Point_3>{};
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