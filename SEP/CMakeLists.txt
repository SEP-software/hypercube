project(hypercube-python)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

find_package(PythonInterp 3 REQUIRED)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../lib")
find_package(pybind11 REQUIRED)  


if (pybind11_FOUND)
  include_directories(${PYTHON_INCLUDE_DIR})
  include_directories(${pybind11_INCLUDE_DIR})
  pybind11_add_module(pySEPException MODULE pySEPException.cpp)
  target_link_libraries(pySEPException PRIVATE  hypercube)
  pybind11_add_module(pyHypercube MODULE pyHyper.cpp)
  target_link_libraries(pyHypercube PRIVATE  hypercube)

  install( TARGETS pyHypercube pySEPException DESTINATION lib/python)
  install(FILES Hypercube.py DESTINATION lib/python)
else(pybind11_FOUND)
endif(pybind11_FOUND)
