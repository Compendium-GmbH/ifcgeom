#pragma once

#include <CGAL/Direction_2.h>
#include <CGAL/Direction_3.h>
#include <CGAL/Point_2.h>
#include <CGAL/Point_3.h>
#include <CGAL/Vector_2.h>
#include <CGAL/Vector_3.h>
#include "CGAL/Aff_transformation_2.h"
#include "CGAL/Aff_transformation_3.h"
#include "CGAL/Exact_predicates_inexact_constructions_kernel.h"
#include "CGAL/Polyhedron_3.h"

#include "IFC2X3/IfcBuildingElementPart.h"
#include "IFC2X3/IfcRelAggregates.h"
#include "IFC2X3/parser.h"

#include "step/write.h"

#include "cista/containers/hash_map.h"
#include "cista/mmap.h"

#include "ifcgeom/tools/filters.h"
#include "ifcgeom/tools/queries.h"

namespace ifcgeom {

using K = CGAL::Exact_predicates_inexact_constructions_kernel;

using Xform_3 = CGAL::Aff_transformation_3<K>;
using Xform_2 = CGAL::Aff_transformation_2<K>;
using Polyhedron_3 = CGAL::Polyhedron_3<K>;
using Point_2 = CGAL::Point_2<K>;
using Point_3 = CGAL::Point_3<K>;
using Vector_3 = CGAL::Vector_3<K>;
using Vector_2 = CGAL::Vector_2<K>;
using Direction_3 = CGAL::Direction_3<K>;
using Direction_2 = CGAL::Direction_2<K>;

struct context {
  context() = default;
  explicit context(std::string const& path) { load(path); }

  void load(cista::mmap const& input) {
    model_ = IFC2X3::parse(
        utl::cstr{reinterpret_cast<char const*>(input.data()), input.size()});
    element_part_map_ = create_element_part_map(model_);
  }

  void load(std::string const& path) {
    auto input = cista::mmap{path.c_str(), cista::mmap::protection::READ};
    load(input);
  }

  void write(std::string const& path) const {
    auto out_file = std::ofstream{path};
    step::write(out_file, model_);
  }

  step::model model_;
  element_part_map element_part_map_;
};

std::vector<std::string> const render_err_log{};
unsigned const render_resolution = 36;
double const tolerance = 0.001;

std::vector<context> const contexts;

}  // namespace ifcgeom
