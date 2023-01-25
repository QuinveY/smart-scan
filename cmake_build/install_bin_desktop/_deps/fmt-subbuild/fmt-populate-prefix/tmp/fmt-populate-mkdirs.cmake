# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/GitHub/smart-scan/cmake_build/install_bin_desktop/_deps/fmt-src"
  "D:/GitHub/smart-scan/cmake_build/install_bin_desktop/_deps/fmt-build"
  "D:/GitHub/smart-scan/cmake_build/install_bin_desktop/_deps/fmt-subbuild/fmt-populate-prefix"
  "D:/GitHub/smart-scan/cmake_build/install_bin_desktop/_deps/fmt-subbuild/fmt-populate-prefix/tmp"
  "D:/GitHub/smart-scan/cmake_build/install_bin_desktop/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp"
  "D:/GitHub/smart-scan/cmake_build/install_bin_desktop/_deps/fmt-subbuild/fmt-populate-prefix/src"
  "D:/GitHub/smart-scan/cmake_build/install_bin_desktop/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/GitHub/smart-scan/cmake_build/install_bin_desktop/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/GitHub/smart-scan/cmake_build/install_bin_desktop/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
