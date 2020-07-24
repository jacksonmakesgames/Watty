#----------------------------------------------------------------
# Generated CMake target import file for configuration "Web".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "freetype" for configuration "Web"
set_property(TARGET freetype APPEND PROPERTY IMPORTED_CONFIGURATIONS WEB)
set_target_properties(freetype PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_WEB "C;RC"
  IMPORTED_LOCATION_WEB "${_IMPORT_PREFIX}/lib/freetype.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS freetype )
list(APPEND _IMPORT_CHECK_FILES_FOR_freetype "${_IMPORT_PREFIX}/lib/freetype.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
