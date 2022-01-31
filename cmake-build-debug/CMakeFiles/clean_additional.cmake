# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/appBookManager_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/appBookManager_autogen.dir/ParseCache.txt"
  "appBookManager_autogen"
  )
endif()
