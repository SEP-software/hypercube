cmake_minimum_required(VERSION 3.5)
project(hypercube)

 include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES axis.cpp hypercube.cpp ioTypes.cc header.cpp debug.cc)
set(INCLUDES axis.h hypercube.h ioTypes.h header.h SEPException.h debug.h)
set(SOURCES  ioTypes.cc  debug.cc
axis.cpp  
hypercube.cpp 
 header.cpp 
)



add_library(hypercube  SHARED ${SOURCES} ${INCLUDES})

target_link_libraries(hypercube m)
target_include_directories(
  hypercube INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
)


  install(FILES ${INCLUDES} DESTINATION include)
    install(TARGETS hypercube DESTINATION lib EXPORT HypercubeTargets)


if(BUILD_TEST)
add_executable(testAxis testAxis.cc)
target_link_libraries(testAxis hypercube gtest gtest_main gtest)
add_test(NAME axis COMMAND testAxis)

add_executable(testHypercube testHypercube.cc)
target_link_libraries(testHypercube hypercube gtest  gtest_main gtest)
add_test(NAME hypercube COMMAND testHypercube)
endif(BUILD_TEST)
