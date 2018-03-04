cmake_minimum_required(VERSION 2.8)
project(logger-python)



  set(min  "${CMAKE_CURRENT_SOURCE_DIR}/logger.in")
  set(mout "${CMAKE_CURRENT_BINARY_DIR}/logger")
  configure_file (${min} ${mout})


install(FILES  ${mout}  DESTINATION share/modules)

