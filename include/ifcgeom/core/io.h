#pragma once
#include <string_view>
#include <vector>

#include "ifcgeom/core/context.h"

#include "boost/algorithm/string.hpp"
#include "boost/filesystem.hpp"

#include "utl/pipes.h"
#include "utl/to_vec.h"

namespace ifcgeom {

namespace fs = boost::filesystem;

inline std::vector<fs::path> get_ifc_paths(fs::path const& dir) {
  return utl::all(boost::make_iterator_range(
             fs::recursive_directory_iterator(dir))) |
         utl::remove_if(
             [](auto&& p) { return p.path().extension() != ".ifc"; }) |
         utl::transform([](auto&& p) { return p.path(); }) | utl::vec();
}

}  // namespace ifcgeom
