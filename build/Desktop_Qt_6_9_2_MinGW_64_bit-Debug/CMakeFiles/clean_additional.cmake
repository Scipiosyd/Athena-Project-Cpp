# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "AthenaProject_autogen"
  "CMakeFiles\\AthenaProject_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\AthenaProject_autogen.dir\\ParseCache.txt"
  )
endif()
