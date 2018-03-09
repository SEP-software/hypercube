project(logger)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

# configure a header file to pass some of the CMake settings

set(logger_MAJOR_VERSION 0)
set(logger_MINOR_VERSION 0)
set(logger_VERSION_STRING
  ${logger_MAJOR_VERSION}.${logger_MINOR_VERSION})



 
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


 SET(logger_DIRNAME_lib     "lib")
 SET(logger_DIRNAME_include "include")
INCLUDE(CMakePackageConfigHelpers)
  CONFIGURE_PACKAGE_CONFIG_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/loggerConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/loggerConfig.cmake"
  INSTALL_DESTINATION
    ${logger_DIRNAME_lib}
  PATH_VARS
    logger_DIRNAME_include
    logger_DIRNAME_lib
  )


  
  INSTALL(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/loggerConfig.cmake
  DESTINATION
    lib
  )


  INSTALL(
  EXPORT
   loggerExports
  DESTINATION
    ${logger_DIRNAME_lib}
  )
  
add_subdirectory(lib)
add_subdirectory(python)

add_subdirectory(env-modules)

