# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\test_mouse_event_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\test_mouse_event_autogen.dir\\ParseCache.txt"
  "test_mouse_event_autogen"
  )
endif()
