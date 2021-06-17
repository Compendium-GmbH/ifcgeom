#include <chrono>
#include <fstream>
#include <iostream>

#include "IFC2X3/IfcProductRepresentation.h"
#include "IFC2X3/IfcRepresentation.h"

#include "ifcgeom/core/analysis.h"
#include "ifcgeom/core/context.h"
#include "ifcgeom/core/io.h"
#include "ifcgeom/core/match.h"

int main(int argc, char** argv) {
  if (argc != 3) {
    std::cout << "Usage: " << argv[0] << " <IFC path> <mode>";
    return 1;
  }

  auto const start = std::chrono::high_resolution_clock::now();
  auto const paths = ifcgeom::get_ifc_paths(argv[1]);

  if (argv[2] == std::string("SINGLE")) {
    for (int i = 0; i < paths.size(); ++i) {
      std::ifstream in{paths.at(i), std::ifstream::ate | std::ifstream::binary};
      std::cout << "Loading context [" << i + 1 << "/" << paths.size()
                << "] : " << paths.at(i).c_str() << " ("
                << in.tellg() / 1000000.00 << " MB)" << std::endl;
      ifcgeom::list_geometry_types(paths.at(i).string());

      std::cout << std::endl;
      ifcgeom::print_distribution(ifcgeom::render_err_log);
      ifcgeom::render_err_log = {};
    }
  } else if (argv[2] == std::string("UNION")) {
    for (int i = 0; i < paths.size(); ++i) {
      std::cout << "Loading context [" << i + 1 << "/" << paths.size()
                << "] : " << paths.at(i).c_str() << std::endl;
      ifcgeom::list_geometry_types(paths.at(i).string());
    }
    std::cout << std::endl;
    ifcgeom::print_distribution(ifcgeom::render_err_log);
    ifcgeom::render_err_log = {};
  } else {
    std::cout << "Please Provide a Mapping Method (SINGLE / UNION)\n";
  }

  std::cout << std::endl;
  auto const end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> ms_double = end - start;
  std::cout << "Mapped Geometries in " << ms_double.count() / 1000
            << " Seconds !" << std::endl;
}
