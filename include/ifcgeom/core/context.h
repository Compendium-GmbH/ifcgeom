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

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef CGAL::Aff_transformation_3<K> Xform_3;
typedef CGAL::Aff_transformation_2<K> Xform_2;
typedef CGAL::Polyhedron_3<K> Polyhedron_3;
typedef CGAL::Point_2<K> Point_2;
typedef CGAL::Point_3<K> Point_3;
typedef CGAL::Vector_3<K> Vector_3;
typedef CGAL::Vector_2<K> Vector_2;
typedef CGAL::Direction_3<K> Direction_3;
typedef CGAL::Direction_2<K> Direction_2;

struct context {
  context() = default;
  context(std::string const& path) { load(path); }

  void load(cista::mmap const& input) {
    model_ = IFC2X3::parse(
        utl::cstr{reinterpret_cast<char const*>(input.data()), input.size()});
    element_part_map_ = create_element_part_map(model_);
  }

  void load(std::string const& path) {
    auto input = cista::mmap{path.c_str(), cista::mmap::protection::READ};
    load(input);
  }

  void write(std::string const& path) {
    auto out_file = std::ofstream{path};
    step::write(out_file, model_);
  }

  step::model model_;
  element_part_map element_part_map_;
};

std::vector<std::string> render_err_log_;
unsigned render_resolution_ = 36;
double tolerance_ = 0.001;

std::vector<context> contexts;

}  // namespace ifcgeom
