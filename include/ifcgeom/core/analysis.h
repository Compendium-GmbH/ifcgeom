#pragma once

#include <algorithm>
#include <vector>

namespace ifcgeom {

template <typename T>
std::vector<T> unique_values(std::vector<T>& input_vec) {
  std::vector<T> uniques(input_vec.size());
  typename std::vector<T>::iterator it;
  it = std::unique_copy(input_vec.begin(), input_vec.end(), uniques.begin());

  std::sort(uniques.begin(), it);
  it = std::unique_copy(uniques.begin(), it, uniques.begin());
  uniques.resize(std::distance(uniques.begin(), it));

  return uniques;
}

template <typename T>
std::vector<int> count_unique_values(std::vector<T>& input_vec) {
  std::vector<T> uniques = unique_values<T>(input_vec);
  std::vector<int> counts(uniques.size());

  for (size_t i = 0; i < counts.size(); ++i)
    counts[i] = std::count(input_vec.begin(), input_vec.end(), uniques[i]);

  return counts;
}

}  // namespace ifcgeom
