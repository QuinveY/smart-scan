cmake_minimum_required(VERSION 3.4)
project(smart-scan LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)

set(SERVICE D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/smart_scan_reformatted/SmartScanService)
set(H_files D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/smart_scan_reformatted/SmartScanService/smartscan_inc)
set(S_files D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/smart_scan_reformatted/SmartScanService/smartscan_src)
#set(simpleble D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/smart_scan_reformatted/simpleble_install/simpleble)
set(simpleble_examples D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/smart_scan_reformatted/simpleble_install/examples/simpleble)
set(BIN D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/install_bin)

add_executable(main_file SmartScanCLI.cpp)

target_include_directories(main_file PRIVATE ${SERVICE})  
target_include_directories(main_file PRIVATE ${H_files})
target_include_directories(main_file PRIVATE ${S_files})
target_include_directories(main_file PRIVATE ${simpleble_examples})
		

add_subdirectory(SmartScanService ${BIN}/SmartScanService)
#add_subdirectory(${simpleble} ${BIN}/simpleble)
add_subdirectory(${simpleble_examples} ${BIN}/simpleble_examples)
#target_link_libraries(main_file simpleble_examples::simpleble_examples)   
target_link_libraries(main_file simpleble::simpleble)           
target_link_libraries(main_file SmartScanService) 

#target_sources(main_file PRIVATE ${SOURCES})
								 
