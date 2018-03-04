cmake_minimum_required(VERSION 2.8)
project(logger)

set(SOURCES logger.cpp
 
)
set(INCLUDES logger.h
)


add_library(logger ${SOURCES} ${INCLUDES})
install(FILES ${INCLUDES} DESTINATION include)
install(TARGETS logger DESTINATION lib EXPORT loggerExports)
