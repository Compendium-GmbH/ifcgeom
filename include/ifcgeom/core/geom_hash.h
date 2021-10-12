#include <algorithm>
#include <iostream>

#include "ifcgeom/core/types.h"

namespace ifcgeom {

template <bool Debug = false>
inline double geom_hash(std::vector<Point_3> vertices) {
  std::sort(vertices.begin(), vertices.end(),
            [](auto const& a, auto const& b) { return a.x() < b.x(); });
  auto const x_min = vertices.front().x();
  auto const x_max = vertices.back().x();
  auto const x_diff = x_max * x_max - x_min * x_min;
  auto const x_center = (vertices.back().x() + vertices.front().x()) / 2;

  std::sort(vertices.begin(), vertices.end(),
            [](auto const& a, auto const& b) { return a.y() < b.y(); });
  auto const y_min = vertices.front().y();
  auto const y_max = vertices.back().y();
  auto const y_diff = y_max * y_max - y_min * y_min;
  auto const y_center = (vertices.back().y() + vertices.front().y()) / 2;

  std::sort(vertices.begin(), vertices.end(),
            [](auto const& a, auto const& b) { return a.z() < b.z(); });
  auto const z_min = vertices.front().z();
  auto const z_max = vertices.back().z();
  auto const z_diff = z_max * z_max - z_min * z_min;
  auto const z_center = (vertices.back().z() + vertices.front().z()) / 2;

  auto const c = x_center + y_center * 1.2 + z_center * 1.4;
  auto const vol = x_diff * y_diff * z_diff;

  if (Debug) {
    std::cout << "Bounding box:\n"
              << "  X: " << x_min << " - " << x_max << "\n"
              << "  Y: " << y_min << " - " << y_max << "\n"
              << "  Z: " << z_min << " - " << z_max << "\n"
              << "Avg: " << c << "\n"
              << "Bv: " << vol << "\n";
  }

  return c * vol;
}

}  // namespace ifcgeom