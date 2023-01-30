#Cmake basic configuration
cmake_minimum_required(VERSION 3.4)#For best result, force cmake to use version 3.4 or above.
project(smart-scan)# This is what your .sln file will be called.
enable_language(CXX)
set(CMAKE_CXX_STANDARD_REQUIRED)


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

##Sources for the SmartScan files.
set(smartscan_SmartScan 	    ${CMAKE_CURRENT_SOURCE_DIR}/SmartScanCli/SmartScanCLI.cpp
                        ${CMAKE_CURRENT_SOURCE_DIR}/SmartScanCli/SmartScanConfig.h)
		

#Add the necessary subdirectories so that the individual libraries run their little CMake Scripts.
add_subdirectory(SmartScanService ${CMAKE_CURRENT_BINARY_DIR}/SmartScanService)
add_subdirectory(Build 		      ${CMAKE_CURRENT_BINARY_DIR}/ATC3DG64)

#Copy over the .dll file needed for the ATC library cus windows hates me.
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${smartscan_build}/ATC3DG64.DLL
     DESTINATION ${EXECUTABLE_OUTPUT_PATH})
file(COPY ${smartscan_build}/ATC3DG64.DLL
     DESTINATION ${EXECUTABLE_OUTPUT_PATH}/ATC3DG64/Debug)
file(COPY ${smartscan_lib}/ATC3DG64.lib
     DESTINATION ${EXECUTABLE_OUTPUT_PATH}/ATC3DG64/Debug)
#Create the SmartScan project thats gonna show up on your smart-scan.sln.
add_executable(SmartScan ${smartscan_SmartScan})
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SmartScan) #Sets your project to SmartScan, so you can debug easily.
#Basic Include directories to avoid dependency errors/missing files.
target_include_directories(SmartScan PRIVATE ${smartscan_cli})
target_include_directories(SmartScan PRIVATE ${smartscan_service})
target_include_directories(SmartScan PRIVATE ${smartscan_build})
target_include_directories(SmartScan PRIVATE ${smartscan_lib})


#Link the necessary libraries so that SmartScan can utilize the BLE, SmartScanService and AT libraries and functions.
target_link_libraries(SmartScan PRIVATE ATC3DG64)
target_link_libraries(SmartScan PRIVATE SmartScanService)   
target_link_libraries(SmartScan PRIVATE simpleble::simpleble)
#Installable Setup
install(TARGETS ATC3DG64 RUNTIME DESTINATION bin)
install(TARGETS SmartScanService RUNTIME DESTINATION bin)
install(TARGETS SmartScan RUNTIME DESTINATION bin)
include(InstallRequiredSystemLibraries)
set(CPACK_SOURCE_GENERATOR "TGZ")
include(CPack)