#include "ifcgeom/geometric_repr_item/boolean_result.h"

#include <chrono>
#include <vector>

#include "boost/iterator/function_output_iterator.hpp"

#include "utl/concat.h"
#include "utl/parser/cstr.h"

#include "CGAL/Polygon_mesh_processing/border.h"
#include "CGAL/Polygon_mesh_processing/corefinement.h"
#include "CGAL/Polygon_mesh_processing/remesh.h"

#include "CGAL/convex_hull_3.h"

#include "IFC2X3/IfcBooleanClippingResult.h"
#include "IFC2X3/IfcBooleanResult.h"

#include "ifcgeom/geometric_repr_item/half_space_solid.h"
#include "ifcgeom/geometric_repr_item/solid_model.h"

#include "ifcgeom/core/context.h"
#include "ifcgeom/core/match.h"

namespace ifcgeom {

using halfedge_descriptor = boost::graph_traits<Mesh>::halfedge_descriptor;
using edge_descriptor = boost::graph_traits<Mesh>::edge_descriptor;

struct halfedge2edge {
  halfedge2edge(const Mesh& m, std::vector<edge_descriptor>& edges)
      : m_mesh(m), m_edges(edges) {}
  void operator()(const halfedge_descriptor& h) const {
    m_edges.push_back(edge(h, m_mesh));
  }
  const Mesh& m_mesh;
  std::vector<edge_descriptor>& m_edges;
};

void prepare_mesh(Mesh& mesh) {
  std::vector<edge_descriptor> border;
  CGAL::Polygon_mesh_processing::border_halfedges(
      CGAL::faces(mesh), mesh,
      boost::make_function_output_iterator(halfedge2edge(mesh, border)));
  CGAL::Polygon_mesh_processing::split_long_edges(border, edge_length, mesh);
  CGAL::Polygon_mesh_processing::isotropic_remeshing(
      faces(mesh), edge_length, mesh,
      CGAL::Polygon_mesh_processing::parameters::number_of_iterations(3)
          .protect_constraints(true));
}

std::vector<Point_3> boolean_result(IFC2X3::IfcBooleanResult const* res) {
  auto get_vertices = [](auto& variant) {
    return std::visit(
        [&](auto item) {
          return match(item, solid_model_handler, half_space_solid_handler,
                       boolean_result);
        },
        variant);
  };

  auto v_first = get_vertices(res->FirstOperand_.data_);
  auto v_second = get_vertices(res->SecondOperand_.data_);

  Mesh mesh_1, mesh_2;
  CGAL::convex_hull_3(v_first.begin(), v_first.end(), mesh_1);
  CGAL::convex_hull_3(v_second.begin(), v_second.end(), mesh_2);

  //  prepare_mesh(mesh_1);
  //  prepare_mesh(mesh_2);

  Mesh boolean_result;
  switch (res->Operator_) {
    case IFC2X3::IfcBooleanOperator::IFC2X3_UNION:
      CGAL::Polygon_mesh_processing::corefine_and_compute_union(mesh_1, mesh_2,
                                                                boolean_result);
      break;
    case IFC2X3::IfcBooleanOperator::IFC2X3_DIFFERENCE:
      CGAL::Polygon_mesh_processing::corefine_and_compute_difference(
          mesh_1, mesh_2, boolean_result);
      break;
    case IFC2X3::IfcBooleanOperator::IFC2X3_INTERSECTION:
      CGAL::Polygon_mesh_processing::corefine_and_compute_intersection(
          mesh_1, mesh_2, boolean_result);
      break;
  }
  return std::vector<Point_3>{};
}

std::vector<Point_3> boolean_clipping_result(
    IFC2X3::IfcBooleanClippingResult const* res) {
  std::vector<Point_3> vertices;
  render_err_log.emplace_back(std::string{res->name()});
  return vertices;
}

std::vector<Point_3> boolean_result_handler(IFC2X3::IfcBooleanResult* item) {
  std::vector<Point_3> vertices{};
  utl::concat(vertices, match(item, boolean_clipping_result, boolean_result));
  return vertices;
}

}  // namespace ifcgeom