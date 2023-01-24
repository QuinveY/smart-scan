#Cmake basic configuration
cmake_minimum_required(VERSION 3.4)#For best result, force cmake to use version 3.4 or above.
project(smart-scan)# This is what your .sln file will be called.



#Basic Compiler options for visual studio, you can also change these in the configuration settings of the project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
##Set the location files
set(smartscan_cli       ${CMAKE_CURRENT_SOURCE_DIR}/SmartScanCli)
set(smartscan_lib       ${CMAKE_CURRENT_SOURCE_DIR}/Lib)
set(smartscan_build     ${CMAKE_CURRENT_SOURCE_DIR}/Build)
set(smartscan_service   ${CMAKE_CURRENT_SOURCE_DIR}/SmartScanService)
set(simpleble 			${CMAKE_CURRENT_SOURCE_DIR}/simpleble_install/simpleble)

##Sources for the main files.
set(smartscan_main 	    ${CMAKE_CURRENT_SOURCE_DIR}/SmartScanCli/SmartScanCLI.cpp
                        ${CMAKE_CURRENT_SOURCE_DIR}/SmartScanCli/SmartScanConfig.h)
						
##Copy over the .dll file needed for the ATC library cus windows hates me.
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${smartscan_build}/ATC3DG64.DLL
     DESTINATION ${EXECUTABLE_OUTPUT_PATH})

#Add the necessary subdirectories so that the individual libraries run their little CMake Scripts.
add_subdirectory(${simpleble}	  ${CMAKE_CURRENT_BINARY_DIR}/simpleble)
add_subdirectory(SmartScanService ${CMAKE_CURRENT_BINARY_DIR}/SmartScanService)
add_subdirectory(Build 			  ${CMAKE_CURRENT_BINARY_DIR}/Build)

#Create the main project thats gonna show up on your smart-scan.sln.
add_executable(main ${smartscan_main})
#Basic Include directories to avoid dependency errors/missing files.
target_include_directories(main PRIVATE ${smartscan_cli})
target_include_directories(main PRIVATE ${smartscan_service})
target_include_directories(main PRIVATE ${smartscan_build})
target_include_directories(main PRIVATE ${smartscan_lib})


#Link the necessary libraries so that main can utilize the BLE, SmartScanService and AT libraries and functions.
target_link_libraries(main PRIVATE ${smartscan_lib}/ATC3DG64.lib)
target_link_libraries(main PRIVATE SmartScanService) 
target_link_libraries(main PRIVATE simpleble::simpleble)           
						 
