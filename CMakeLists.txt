cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

if(NOT SUBPACKAGE) 
  option(BUILD_PYTHON "Build python interfaces" ON)
endif(NOT SUBPACKAGE)
set(SUBPACKAGE true)

project(hypercube LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE True)
# configure a header file to pass some of the CMake settings

set(hypercube_MAJOR_VERSION 0)
set(hypercube_MINOR_VERSION 2)
set(hypercube_VERSION_STRING
    ${hypercube_MAJOR_VERSION}.${hypercube_MINOR_VERSION})

include_directories("${PROJECT_BINARY_DIR}")

set(hypercube_DIRNAME_cmake "cmake")
set(hypercube_DIRNAME_lib "lib")
set(hypercube_DIRNAME_include "include")

include(CMakePackageConfigHelpers)

if(NOT SUPPORT_LIBRARIES_BUILD)
configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/hypercubeConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/hypercubeConfig.cmake"
  INSTALL_DESTINATION
  ${hypercube_DIRNAME_cmake}
  PATH_VARS
  hypercube_DIRNAME_include
  hypercube_DIRNAME_lib
  hypercube_DIRNAME_cmake)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/hypercubeConfig.cmake
        DESTINATION cmake)

install(EXPORT hypercubeExports DESTINATION ${hypercube_DIRNAME_cmake})
endif(NOT SUPPORT_LIBRARIES_BUILD)
add_subdirectory(lib)
if(BUILD_PYTHON)
  add_subdirectory(python)
endif(BUILD_PYTHON)

add_subdirectory(env-modules)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${hypercube_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${hypercube_MINOR_VERSION}")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_NAME "hypercube")
set(CPACK_PACKAGE_CONTACT "Robert Clapp")
include(CPack)
