project(hypercube-python)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../lib")
find_package(pybind11)  
if (pybind11_FOUND)
include_directories(${PYTHON_INCLUDE_DIR})
include_directories(${pybind11_INCLUDE_DIR})
pybind11_add_module(pyLogger MODULE pyLogger.cpp)
target_link_libraries(pyLogger PRIVATE  logger)

install( TARGETS pyLogger DESTINATION lib/python)
install(FILES Logger.py DESTINATION lib/python)
endif(pybind11_FOUND)