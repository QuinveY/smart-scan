# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/Github/smart-scan/cmake_build/install_bin/_deps/fmt-src"
  "D:/Github/smart-scan/cmake_build/install_bin/_deps/fmt-build"
  "D:/Github/smart-scan/cmake_build/install_bin/_deps/fmt-subbuild/fmt-populate-prefix"
  "D:/Github/smart-scan/cmake_build/install_bin/_deps/fmt-subbuild/fmt-populate-prefix/tmp"
  "D:/Github/smart-scan/cmake_build/install_bin/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp"
  "D:/Github/smart-scan/cmake_build/install_bin/_deps/fmt-subbuild/fmt-populate-prefix/src"
  "D:/Github/smart-scan/cmake_build/install_bin/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Github/smart-scan/cmake_build/install_bin/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/Github/smart-scan/cmake_build/install_bin/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
