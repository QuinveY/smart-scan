# Install script for directory: D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/smart_scan_reformatted/simpleble_install/examples/simpleble

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
  include("D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/install_bin/simpleble/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/install_bin/simpleble_examples/cpp/list_adapters/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/install_bin/simpleble_examples/cpp/scan/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/install_bin/simpleble_examples/cpp/connect/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/install_bin/simpleble_examples/cpp/connect_safe/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/install_bin/simpleble_examples/cpp/read/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/install_bin/simpleble_examples/cpp/write/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/install_bin/simpleble_examples/cpp/notify/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/install_bin/simpleble_examples/cpp/notify_multi/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/install_bin/simpleble_examples/c/notify/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/install_bin/simpleble_examples/c/connect/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/install_bin/simpleble_examples/c/scan/cmake_install.cmake")
endif()

