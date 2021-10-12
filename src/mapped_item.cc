#include "ifcgeom/mapped_item.h"

#include <vector>

#include "IFC2X3/IfcMappedItem.h"
#include "IFC2X3/IfcRepresentationMap.h"

#include "ifcgeom/core/render.h"
#include "ifcgeom/core/xform.h"

namespace ifcgeom {

std::vector<Point_3> mapped_item(IFC2X3::IfcMappedItem const* item) {
  std::vector<Point_3> vertices =
      ifcgeom::gather_vertices(item->MappingSource_->MappedRepresentation_);
  return ifcgeom::cartesian_transformation(item->MappingTarget_, vertices);
}

}  // namespace ifcgeom
