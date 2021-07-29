#include <algorithm>
#include <iostream>

#include "ifcgeom/core/types.h"

namespace ifcgeom {

template <bool Debug = false>
inline double geom_hash(std::vector<Point_3> vertices) {
  std::sort(vertices.begin(), vertices.end(),
            [](auto const& a, auto const& b) { return a.x() < b.x(); });
  auto const x_diff = vertices.back().x() - vertices.front().x();
  auto const x_avg = (vertices.back().x() + vertices.front().x()) / 2;

  std::sort(vertices.begin(), vertices.end(),
            [](auto const& a, auto const& b) { return a.y() < b.y(); });
  auto const y_diff = vertices.back().y() - vertices.front().y();
  auto const y_avg = (vertices.back().y() + vertices.front().y()) / 2;

  std::sort(vertices.begin(), vertices.end(),
            [](auto const& a, auto const& b) { return a.z() < b.z(); });
  auto const z_diff = vertices.back().z() - vertices.front().z();
  auto const z_avg = (vertices.back().z() + vertices.front().z()) / 2;

  auto const avg = x_avg + y_avg * 1.2 + z_avg * 1.4;
  auto const bv = x_diff * y_diff * z_diff;

  if (Debug) {
    std::cout << "Bounding box:\n"
              << "  X: " << vertices.back().x() << " - " << vertices.front().x()
              << "\n"
              << "  Y: " << vertices.back().y() << " - " << vertices.front().y()
              << "\n"
              << "  Z: " << vertices.back().z() << " - " << vertices.front().z()
              << "\n"
              << "Avg: " << avg << "\n"
              << "Bv: " << bv << "\n";
  }

  return avg * bv;
}

}  // namespace ifcgeom