#include "ifcgeom/core/context.h"

#include "IFC2X3/IfcRelAggregates.h"
#include "IFC2X3/parser.h"

#include "step/write.h"

#include "cista/mmap.h"

#include "ifcgeom/core/queries.h"

namespace ifcgeom {

context::context() = default;

context::context(const std::string& path) { load(path); }

void context::load(cista::mmap const& input) {
  model_ = IFC2X3::parse(
      utl::cstr{reinterpret_cast<char const*>(input.data()), input.size()});
  element_part_map_ = create_element_part_map(model_);
}

void context::load(std::string const& path) {
  auto input = cista::mmap{path.c_str(), cista::mmap::protection::READ};
  load(input);
}

void context::write(std::string const& path) const {
  auto out_file = std::ofstream{path};
  step::write(out_file, model_);
}

std::vector<std::string> render_err_log{};

}  // namespace ifcgeom
