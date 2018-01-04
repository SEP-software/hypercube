project(Generic-IO)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)



# This is a CMake example for Python

FIND_PACKAGE(SWIG REQUIRED)
if(SWIG_FOUND)
MESSAGE("found SWIG building python interface")
INCLUDE(${SWIG_USE_FILE})

FIND_PACKAGE(PythonLibs)
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../lib)
INCLUDE_DIRECTORIES(${GENERIC_EXPORT_INC_DIRS})

SET(CMAKE_SWIG_FLAGS "")

SET_SOURCE_FILES_PROPERTIES(hypercube_int.i PROPERTIES CPLUSPLUS ON)
SWIG_ADD_MODULE(hypercube_int python hypercube_int.i ../lib/hypercube.cpp)
SWIG_LINK_LIBRARIES(hypercube_int hypercube ${PYTHON_LIBRARIES})


SWIG_LINK_LIBRARIES(hypercube_int  hypercube  ${PYTHON_LIBRARIES})

set(PYS
${CMAKE_BINARY_DIR}/python/hypercube_int.py
)
install(FILES ${PYS} DESTINATION lib/python/SEP)

else(SWIG_FOUND)
MESSAGE("Did not find SWIG, not building python interface")
endif(SWIG_FOUND)
