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

}  // namespace ifcgeom
