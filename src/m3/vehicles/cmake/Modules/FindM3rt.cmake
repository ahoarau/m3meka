# - Try to find m3base
# Once done this will define
#  M3RT_FOUND - System has M3RT
#  M3RT_INCLUDE_DIRS - The M3RT include directories
#  M3RT_LIBRARIES - The libraries needed to use M3RT
#  M3RT_DEFINITIONS - Compiler switches required for using M3RT
#####if(M3RT_INCLUDE_DIR)
#####SET(M3RT_FOUND TRUE)
#####else(M3RT_INCLUDE_DIR)
#find_package(PkgConfig)
#pkg_check_modules(M3RT_BASE QUIET m3base)

find_path(M3RT_INCLUDE_DIR NAMES m3rt
     PATHS
     ${INCLUDE_INSTALL_DIR}
     PATH_SUFFIXES include
   )

find_library(M3RT_LIBRARY NAMES m3base 
             HINTS ${M3RT_LIBDIR} ${M3RT_LIBRARY_DIRS} )

set(M3RT_LIBRARIES ${M3RT_LIBRARY} )
set(M3RT_INCLUDE_DIRS ${M3RT_INCLUDE_DIR} ${M3RT_INCLUDE_DIR}/m3rt/base ${M3RT_INCLUDE_DIR}/m3rt/rt_system)
set(M3RT_INCLUDE_DIR ${M3RT_INCLUDE_DIRS})
include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set M3RT_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(M3RT  DEFAULT_MSG
                                  M3RT_LIBRARY M3RT_INCLUDE_DIR)
message("-- M3rt include dir: ${M3RT_INCLUDE_DIRS}")
message("-- M3rt base library: ${M3RT_LIBRARIES}")
mark_as_advanced(M3RT_INCLUDE_DIR M3RT_LIBRARIES )
######endif(M3RT_INCLUDE_DIR)
