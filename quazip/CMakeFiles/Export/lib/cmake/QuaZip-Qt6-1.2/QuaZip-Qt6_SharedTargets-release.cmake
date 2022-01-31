#----------------------------------------------------------------
# Generated CMake target import file for configuration "RELEASE".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "QuaZip::QuaZip" for configuration "RELEASE"
set_property(TARGET QuaZip::QuaZip APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(QuaZip::QuaZip PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libquazip1-qt6.so.1.2"
  IMPORTED_SONAME_RELEASE "libquazip1-qt6.so.1.0.0"
  )

list(APPEND _IMPORT_CHECK_TARGETS QuaZip::QuaZip )
list(APPEND _IMPORT_CHECK_FILES_FOR_QuaZip::QuaZip "${_IMPORT_PREFIX}/lib/libquazip1-qt6.so.1.2" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
