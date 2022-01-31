# Install script for directory: /home/johan/Programmering/QT/BookManager/lib/quazip-master/quazip

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RELEASE")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libquazip1-qt6.so.1.2"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libquazip1-qt6.so.1.0.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/johan/Programmering/QT/BookManager/lib/quazip-master/quazip/libquazip1-qt6.so.1.2"
    "/home/johan/Programmering/QT/BookManager/lib/quazip-master/quazip/libquazip1-qt6.so.1.0.0"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libquazip1-qt6.so.1.2"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libquazip1-qt6.so.1.0.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/usr/local/lib:"
           NEW_RPATH "")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libquazip1-qt6.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libquazip1-qt6.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libquazip1-qt6.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/johan/Programmering/QT/BookManager/lib/quazip-master/quazip/libquazip1-qt6.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libquazip1-qt6.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libquazip1-qt6.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libquazip1-qt6.so"
         OLD_RPATH "/usr/local/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libquazip1-qt6.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/QuaZip-Qt6-1.2/quazip" TYPE FILE FILES
    "/home/johan/Programmering/QT/BookManager/lib/quazip-master/quazip/JlCompress.h"
    "/home/johan/Programmering/QT/BookManager/lib/quazip-master/quazip/ioapi.h"
    "/home/johan/Programmering/QT/BookManager/lib/quazip-master/quazip/minizip_crypt.h"
    "/home/johan/Programmering/QT/BookManager/lib/quazip-master/quazip/quaadler32.h"
    "/home/johan/Programmering/QT/BookManager/lib/quazip-master/quazip/quachecksum32.h"
    "/home/johan/Programmering/QT/BookManager/lib/quazip-master/quazip/quacrc32.h"
    "/home/johan/Programmering/QT/BookManager/lib/quazip-master/quazip/quagzipfile.h"
    "/home/johan/Programmering/QT/BookManager/lib/quazip-master/quazip/quaziodevice.h"
    "/home/johan/Programmering/QT/BookManager/lib/quazip-master/quazip/quazip.h"
    "/home/johan/Programmering/QT/BookManager/lib/quazip-master/quazip/quazip_global.h"
    "/home/johan/Programmering/QT/BookManager/lib/quazip-master/quazip/quazip_qt_compat.h"
    "/home/johan/Programmering/QT/BookManager/lib/quazip-master/quazip/quazipdir.h"
    "/home/johan/Programmering/QT/BookManager/lib/quazip-master/quazip/quazipfile.h"
    "/home/johan/Programmering/QT/BookManager/lib/quazip-master/quazip/quazipfileinfo.h"
    "/home/johan/Programmering/QT/BookManager/lib/quazip-master/quazip/quazipnewinfo.h"
    "/home/johan/Programmering/QT/BookManager/lib/quazip-master/quazip/unzip.h"
    "/home/johan/Programmering/QT/BookManager/lib/quazip-master/quazip/zip.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/QuaZip-Qt6-1.2/QuaZip-Qt6_SharedTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/QuaZip-Qt6-1.2/QuaZip-Qt6_SharedTargets.cmake"
         "/home/johan/Programmering/QT/BookManager/lib/quazip-master/quazip/CMakeFiles/Export/lib/cmake/QuaZip-Qt6-1.2/QuaZip-Qt6_SharedTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/QuaZip-Qt6-1.2/QuaZip-Qt6_SharedTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/QuaZip-Qt6-1.2/QuaZip-Qt6_SharedTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/QuaZip-Qt6-1.2" TYPE FILE FILES "/home/johan/Programmering/QT/BookManager/lib/quazip-master/quazip/CMakeFiles/Export/lib/cmake/QuaZip-Qt6-1.2/QuaZip-Qt6_SharedTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/QuaZip-Qt6-1.2" TYPE FILE FILES "/home/johan/Programmering/QT/BookManager/lib/quazip-master/quazip/CMakeFiles/Export/lib/cmake/QuaZip-Qt6-1.2/QuaZip-Qt6_SharedTargets-release.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/QuaZip-Qt6-1.2" TYPE FILE FILES
    "/home/johan/Programmering/QT/BookManager/lib/quazip-master/quazip/QuaZip-Qt6Config.cmake"
    "/home/johan/Programmering/QT/BookManager/lib/quazip-master/quazip/QuaZip-Qt6ConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/johan/Programmering/QT/BookManager/lib/quazip-master/quazip/quazip1-qt6.pc")
endif()

