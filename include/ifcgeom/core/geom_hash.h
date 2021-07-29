#include <algorithm>
#include <iostream>
#include <numeric>
#include "ifcgeom/core/types.h"

namespace ifcgeom {

template <bool Debug = false>
inline double geom_hash(std::vector<Point_3> vertices) {
  std::sort(vertices.begin(), vertices.end(),
            [](auto const& a, auto const& b) { return a.x() < b.x(); });
  auto const x_min = vertices.front().x();
  auto const x_max = vertices.back().x();
  auto const x_diff = x_max - x_min;
  // this calculate the average
  auto const x_avg = std::accumulate(vertices.begin(), vertices.end(), 0.0,
                                     [](auto current_value, Point_3 point) {
                                       return current_value + point.x();
                                     }) /
                     static_cast<double>(vertices.size());

  // this only calculate the middle point
  // auto const x_middle = (vertices.back().x() + vertices.front().x()) / 2;

  // in a sorted list we can also take the median for faster hashing
  // int median_index = vertices.size() % 2 ? vertices.size() - 1 :
  // vertices.size();
  // auto const x_median = vertices[median_index].x();

  std::sort(vertices.begin(), vertices.end(),
            [](auto const& a, auto const& b) { return a.y() < b.y(); });
  auto const y_min = vertices.front().y();
  auto const y_max = vertices.back().y();
  auto const y_diff = y_max - y_min;
  auto const y_avg = std::accumulate(vertices.begin(), vertices.end(), 0.0,
                                     [](auto current_value, Point_3 point) {
                                       return current_value + point.y();
                                     }) /
                     static_cast<double>(vertices.size());

  std::sort(vertices.begin(), vertices.end(),
            [](auto const& a, auto const& b) { return a.z() < b.z(); });
  auto const z_min = vertices.front().z();
  auto const z_max = vertices.back().z();
  auto const z_diff = z_max - z_min;
  auto const z_avg = std::accumulate(vertices.begin(), vertices.end(), 0.0,
                                     [](auto current_value, Point_3 point) {
                                       return current_value + point.z();
                                     }) /
                     static_cast<double>(vertices.size());

  // this numbers are empirically choosen to reduce the possibility for hash
  // collision.
  //  double const skew_y = 1.2;
  //  double const skew_z = 1.4;
  //  auto const avg =
  //      x_avg + x_max + (y_avg + y_max) * skew_y + (z_avg + z_max) * skew_z;
  auto const avg = x_avg + y_avg + z_avg;
  std::cout << "(" << x_avg << ", " << x_avg << ", " << x_avg << ")\n";
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
