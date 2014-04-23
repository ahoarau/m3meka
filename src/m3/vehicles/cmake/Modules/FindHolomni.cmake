
# deduce the libraries suffix from the options
if (HOLOMNI_LIBRARY)

  # in cache already
  set(HOLOMNI_FOUND TRUE)

else (HOLOMNI_LIBRARY)

# find the Holomni include directory
find_path(HOLOMNI_INCLUDE_DIR NAMES holomni_pcv
		PATHS
		${INCLUDE_INSTALL_DIR}
		PATH_SUFFIXE holomni_pcv)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Holomni DEFAULT_MSG HOLOMNI_INCLUDE_DIR )

mark_as_advanced(HOLOMNI_INCLUDE_DIR)
  if(Holomni_FOUND)
	set(HOLOMNI_LIBRARIES holomni_pcv PARENT_SCOPE)
  endif(Holomni_FOUND)
endif(HOLOMNI_LIBRARY)
