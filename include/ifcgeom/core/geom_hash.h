#include <algorithm>
#include <iostream>

#include "ifcgeom/core/types.h"

namespace ifcgeom {

struct {
  bool operator()(Point_3 a, Point_3 b) const { return a.x() < b.x(); }
} x_less;

struct {
  bool operator()(Point_3 a, Point_3 b) const { return a.y() < b.y(); }
} y_less;

struct {
  bool operator()(Point_3 a, Point_3 b) const { return a.z() < b.z(); }
} z_less;

inline double geom_hash(std::vector<Point_3> vertices) {
  std::sort(vertices.begin(), vertices.end(), x_less);
  auto x_avg = (vertices.back().x() + vertices.front().x()) / 2;

  std::sort(vertices.begin(), vertices.end(), y_less);
  auto y_avg = (vertices.back().y() + vertices.front().y()) / 2;

  std::sort(vertices.begin(), vertices.end(), z_less);
  auto z_avg = (vertices.back().z() + vertices.front().z()) / 2;

  return x_avg * .1 + y_avg * .2 + z_avg * .3;
}

}  // namespace ifcgeom