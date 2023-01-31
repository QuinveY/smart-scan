#Cmake basic configuration
cmake_minimum_required(VERSION 3.4)#For best result, force cmake to use version 3.4 or above.
project(smart-scan)# This is what your .sln file will be called.
#Cmake should do this automatically, but these settings define C++ as the project language

#Basic Compiler options for visual studio, you can also change these in the configuration settings of the project
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON) #This option helped with LNK issues when initially converting the project, might be obsolete now.

##Set the location files, ${CMAKE_CURRENT_SOURCE_DIR} looks at wherever you have your main folder, you only need to specify the pathing of any folder inside your project
set(smartscan_cli       ${CMAKE_CURRENT_SOURCE_DIR}/SmartScanCli)
set(smartscan_lib       ${CMAKE_CURRENT_SOURCE_DIR}/Lib)
set(smartscan_build     ${CMAKE_CURRENT_SOURCE_DIR}/Build)
set(smartscan_service   ${CMAKE_CURRENT_SOURCE_DIR}/SmartScanService)
set(simpleble 			${CMAKE_CURRENT_SOURCE_DIR}/simpleble_install/simpleble)

##Sources for the SmartScan files, these 2 main files will show up in your SmartScan project part of the solution.
set(smartscan_SmartScan 	    ${CMAKE_CURRENT_SOURCE_DIR}/SmartScanCli/SmartScanCLI.cpp
								${CMAKE_CURRENT_SOURCE_DIR}/SmartScanCli/SmartScanConfig.h)
		

#Add the necessary subdirectories so that the individual libraries run their little CMake Scripts. They will look into these folders expecting a Cmakelists.txt file,  ${CMAKE_CURRENT_BINARY_DIR}/"location" will make a folder with that name in the install location.
#EXECUTABLE_OUTPUT_PATH is set so the name is more self explanatory 
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
add_subdirectory(SmartScanService ${EXECUTABLE_OUTPUT_PATH}/SmartScanService)
add_subdirectory(Build 		      ${EXECUTABLE_OUTPUT_PATH}/ATC3DG64)

#Copy over the .dll and .lib files needed for the ATC library cus windows hates me. This is so that CPack packaging works properly, since it looks for .lib files under Debug. There is probably a much cleaner way to do this, but it works as is.
file(COPY ${smartscan_build}/ATC3DG64.DLL
     DESTINATION ${EXECUTABLE_OUTPUT_PATH})
file(COPY ${smartscan_build}/ATC3DG64.DLL
     DESTINATION ${EXECUTABLE_OUTPUT_PATH}/ATC3DG64/Debug)
file(COPY ${smartscan_lib}/ATC3DG64.lib
     DESTINATION ${EXECUTABLE_OUTPUT_PATH}/ATC3DG64/Debug)
	 
#Create the SmartScan project thats gonna show up on your smart-scan.sln.
add_executable(SmartScan ${smartscan_SmartScan})
#set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SmartScan) #Sets your project to SmartScan, so you can debug easily.

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
#These install functions make sure that cpack packages everything correctly(keep this in mind if you add new libraries.
install(TARGETS ATC3DG64 RUNTIME DESTINATION bin)
install(TARGETS SmartScanService RUNTIME DESTINATION bin)
install(TARGETS SmartScan RUNTIME DESTINATION bin)
include(InstallRequiredSystemLibraries)#Enable Cpack functions
set(CPACK_SOURCE_GENERATOR "TGZ")#Specification of what type of package you want. "TGZ" is for a windows installer. "ZIP" is also an option.
include(CPack)