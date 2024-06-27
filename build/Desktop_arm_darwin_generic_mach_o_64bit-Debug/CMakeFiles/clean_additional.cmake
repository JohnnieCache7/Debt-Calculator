# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/DebtCalculator_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/DebtCalculator_autogen.dir/ParseCache.txt"
  "DebtCalculator_autogen"
  )
endif()
