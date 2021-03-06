#pragma once

#include <string>
#include <vector>

#include "cista/mmap.h"

#include "ifcgeom/core/queries.h"
#include "ifcgeom/core/types.h"

namespace ifcgeom {

struct context {
  context();
  explicit context(std::string const& path);

  void load(cista::mmap const& input);
  void load(std::string const& path);

  void write(std::string const& path) const;

  step::model model_;
  element_part_map element_part_map_;
};

static std::vector<std::string> render_err_log;
unsigned const render_resolution = 36;
double const tolerance = 0.001;

// std::vector<context> const contexts;

}  // namespace ifcgeom
