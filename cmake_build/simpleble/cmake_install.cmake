# Install script for directory: C:/Users/Arjan/Nextcloud/Elektrotechniek/S7/SmartScan porject/smart-scan-git/smart-scan/smart_scan_BLE/simpleble_install/simpleble

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/smart-scan")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/Arjan/Nextcloud/Elektrotechniek/S7/SmartScan porject/smart-scan-git/smart-scan/cmake_build/_deps/fmt-build/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Arjan/Nextcloud/Elektrotechniek/S7/SmartScan porject/smart-scan-git/smart-scan/cmake_build/simpleble/Debug/simpleble.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Arjan/Nextcloud/Elektrotechniek/S7/SmartScan porject/smart-scan-git/smart-scan/cmake_build/simpleble/Release/simpleble.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Arjan/Nextcloud/Elektrotechniek/S7/SmartScan porject/smart-scan-git/smart-scan/cmake_build/simpleble/MinSizeRel/simpleble.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Arjan/Nextcloud/Elektrotechniek/S7/SmartScan porject/smart-scan-git/smart-scan/cmake_build/simpleble/RelWithDebInfo/simpleble.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Arjan/Nextcloud/Elektrotechniek/S7/SmartScan porject/smart-scan-git/smart-scan/cmake_build/simpleble/Debug/simpleble-c.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Arjan/Nextcloud/Elektrotechniek/S7/SmartScan porject/smart-scan-git/smart-scan/cmake_build/simpleble/Release/simpleble-c.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Arjan/Nextcloud/Elektrotechniek/S7/SmartScan porject/smart-scan-git/smart-scan/cmake_build/simpleble/MinSizeRel/simpleble-c.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Arjan/Nextcloud/Elektrotechniek/S7/SmartScan porject/smart-scan-git/smart-scan/cmake_build/simpleble/RelWithDebInfo/simpleble-c.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/simpleble/simpleble-config.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/simpleble/simpleble-config.cmake"
         "C:/Users/Arjan/Nextcloud/Elektrotechniek/S7/SmartScan porject/smart-scan-git/smart-scan/cmake_build/simpleble/CMakeFiles/Export/13b57db71a86868acd3c5f5abbcb6436/simpleble-config.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/simpleble/simpleble-config-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/simpleble/simpleble-config.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/simpleble" TYPE FILE FILES "C:/Users/Arjan/Nextcloud/Elektrotechniek/S7/SmartScan porject/smart-scan-git/smart-scan/cmake_build/simpleble/CMakeFiles/Export/13b57db71a86868acd3c5f5abbcb6436/simpleble-config.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/simpleble" TYPE FILE FILES "C:/Users/Arjan/Nextcloud/Elektrotechniek/S7/SmartScan porject/smart-scan-git/smart-scan/cmake_build/simpleble/CMakeFiles/Export/13b57db71a86868acd3c5f5abbcb6436/simpleble-config-debug.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/simpleble" TYPE FILE FILES "C:/Users/Arjan/Nextcloud/Elektrotechniek/S7/SmartScan porject/smart-scan-git/smart-scan/cmake_build/simpleble/CMakeFiles/Export/13b57db71a86868acd3c5f5abbcb6436/simpleble-config-minsizerel.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/simpleble" TYPE FILE FILES "C:/Users/Arjan/Nextcloud/Elektrotechniek/S7/SmartScan porject/smart-scan-git/smart-scan/cmake_build/simpleble/CMakeFiles/Export/13b57db71a86868acd3c5f5abbcb6436/simpleble-config-relwithdebinfo.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/simpleble" TYPE FILE FILES "C:/Users/Arjan/Nextcloud/Elektrotechniek/S7/SmartScan porject/smart-scan-git/smart-scan/cmake_build/simpleble/CMakeFiles/Export/13b57db71a86868acd3c5f5abbcb6436/simpleble-config-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/simpleble" TYPE DIRECTORY FILES "C:/Users/Arjan/Nextcloud/Elektrotechniek/S7/SmartScan porject/smart-scan-git/smart-scan/smart_scan_BLE/simpleble_install/simpleble/include/simpleble/")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/simpleble" TYPE DIRECTORY FILES "C:/Users/Arjan/Nextcloud/Elektrotechniek/S7/SmartScan porject/smart-scan-git/smart-scan/cmake_build/simpleble/export/simpleble/")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/simpleble_c" TYPE DIRECTORY FILES "C:/Users/Arjan/Nextcloud/Elektrotechniek/S7/SmartScan porject/smart-scan-git/smart-scan/smart_scan_BLE/simpleble_install/simpleble/include/simpleble_c/")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/Arjan/Nextcloud/Elektrotechniek/S7/SmartScan porject/smart-scan-git/smart-scan/cmake_build/simpleble/simpleble.pc")
endif()

