# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles/QtOpenGLNBody_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/QtOpenGLNBody_autogen.dir/ParseCache.txt"
  "QtOpenGLNBody_autogen"
  )
endif()
