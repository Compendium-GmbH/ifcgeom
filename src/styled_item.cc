#include "ifcgeom/styled_item.h"

#include <vector>

#include "IFC2X3/IfcStyledItem.h"

#include "ifcgeom/core/context.h"
#include "ifcgeom/core/match.h"

namespace ifcgeom {

std::vector<Point_3> styled_item(IFC2X3::IfcStyledItem const* item) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{item->name()});
  return vertices;
}

}  // namespace ifcgeom
