cmake_minimum_required(VERSION  3.5)
project(hypercube)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES axis.cpp hypercube.cpp ioTypes.cc header.cpp)
set(INCLUDES axis.h hypercube.h ioTypes.h header.h)

add_library(hypercube ${SOURCES} ${INCLUDES})

if(NOT SUPPORT_LIBRARIES_BUILD)
install(FILES ${INCLUDES} DESTINATION include)
install(TARGETS hypercube DESTINATION lib EXPORT hypercubeExports)
endif(NOT SUPPORT_LIBRARIES_BUILD)
