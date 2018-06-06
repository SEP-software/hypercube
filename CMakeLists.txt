project(hypercube)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)


# configure a header file to pass some of the CMake settings
find_package( PythonInterp 3 REQUIRED )


set(hypercube_MAJOR_VERSION 0)
set(hypercube_MINOR_VERSION 0)
set(hypercube_VERSION_STRING    ${hypercube_MAJOR_VERSION}.${hypercube_MINOR_VERSION})


#Install PYBIND11 

find_package(pybind11)  
if (pybind11_FOUND)
  message("Found pybind11 installed")
else(pybind11_FOUND)
  message("Installing pybind11")
  include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
  ExternalProject_Add (
       PYBIND11
       CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
      GIT_REPOSITORY "https://github.com/pybind/pybind11.git"
            INSTALL_DIR  ${CMAKE_INSTALL_PREFIX}

     )
endif(pybind11_FOUND)
 
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")


include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpic")
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

enable_language(CXX)

 SET(hypercube_DIRNAME_cmake     "cmake")

 SET(hypercube_DIRNAME_lib     "lib")
 SET(hypercube_DIRNAME_include "include")
INCLUDE(CMakePackageConfigHelpers)
  CONFIGURE_PACKAGE_CONFIG_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/hypercubeConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/hypercubeConfig.cmake"
  INSTALL_DESTINATION
    ${hypercube_DIRNAME_lib}
  PATH_VARS
    hypercube_DIRNAME_include
    hypercube_DIRNAME_lib
    hypercube_DIRNAME_cmake
  )


  
  INSTALL(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/hypercubeConfig.cmake
  DESTINATION
    cmake
  )


  INSTALL(
  EXPORT
   hypercubeExports
  DESTINATION
    ${hypercube_DIRNAME_cmake}
  )
  
add_subdirectory(lib)
add_subdirectory(python)

add_subdirectory(env-modules)

