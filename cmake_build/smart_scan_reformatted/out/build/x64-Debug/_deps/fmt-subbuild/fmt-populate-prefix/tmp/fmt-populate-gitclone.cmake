# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

if(EXISTS "D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/smart_scan_reformatted/out/build/x64-Debug/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp/fmt-populate-gitclone-lastrun.txt" AND EXISTS "D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/smart_scan_reformatted/out/build/x64-Debug/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp/fmt-populate-gitinfo.txt" AND
  "D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/smart_scan_reformatted/out/build/x64-Debug/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp/fmt-populate-gitclone-lastrun.txt" IS_NEWER_THAN "D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/smart_scan_reformatted/out/build/x64-Debug/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp/fmt-populate-gitinfo.txt")
  message(STATUS
    "Avoiding repeated git clone, stamp file is up to date: "
    "'D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/smart_scan_reformatted/out/build/x64-Debug/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp/fmt-populate-gitclone-lastrun.txt'"
  )
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/smart_scan_reformatted/out/build/x64-Debug/_deps/fmt-src"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: 'D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/smart_scan_reformatted/out/build/x64-Debug/_deps/fmt-src'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "C:/Program Files/Git/cmd/git.exe" 
            clone --no-checkout --config "advice.detachedHead=false" "https://github.com/fmtlib/fmt.git" "fmt-src"
    WORKING_DIRECTORY "D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/smart_scan_reformatted/out/build/x64-Debug/_deps"
    RESULT_VARIABLE error_code
  )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once: ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/fmtlib/fmt.git'")
endif()

execute_process(
  COMMAND "C:/Program Files/Git/cmd/git.exe" 
          checkout "b6f4ceaed0a0a24ccf575fab6c56dd50ccf6f1a9" --
  WORKING_DIRECTORY "D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/smart_scan_reformatted/out/build/x64-Debug/_deps/fmt-src"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'b6f4ceaed0a0a24ccf575fab6c56dd50ccf6f1a9'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "C:/Program Files/Git/cmd/git.exe" 
            submodule update --recursive --init 
    WORKING_DIRECTORY "D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/smart_scan_reformatted/out/build/x64-Debug/_deps/fmt-src"
    RESULT_VARIABLE error_code
  )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: 'D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/smart_scan_reformatted/out/build/x64-Debug/_deps/fmt-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy "D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/smart_scan_reformatted/out/build/x64-Debug/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp/fmt-populate-gitinfo.txt" "D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/smart_scan_reformatted/out/build/x64-Debug/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp/fmt-populate-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: 'D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/smart_scan_reformatted/out/build/x64-Debug/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp/fmt-populate-gitclone-lastrun.txt'")
endif()
