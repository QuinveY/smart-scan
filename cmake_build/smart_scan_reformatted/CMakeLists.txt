cmake_minimum_required(VERSION 3.4)
project(smart-scan LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
cmake_minimum_required(VERSION 3.13)

set(H_files D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/smart_scan_reformatted/lib_SmartScanService/inc)
set(S_files D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/smart_scan_reformatted/lib_SmartScanService/src)
set(smartscan_service D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/smart_scan_reformatted/lib_SmartScanService)
set(simpleble D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/smart_scan_reformatted/lib_simpleble_install/simpleble)
set(ATC3DG64 D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/smart_scan_reformatted/lib_ATC3DG64)
set(BIN D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/install_bin)


			
add_executable(main_file SmartScanCLI.cpp)

target_include_directories(main_file PRIVATE ${smartscan_service})  
target_include_directories(main_file PRIVATE ${H_files})
target_include_directories(main_file PRIVATE ${S_files})
target_include_directories(main_file PRIVATE ${ATC3DG64})



add_subdirectory(lib_ATC3DG64 ${BIN}/atlibrary)
add_subdirectory(lib_SmartScanService ${BIN}/SmartScanService)
add_subdirectory(${simpleble} ${BIN}/simpleble)

target_link_libraries(SmartScanService INTERFACE atlib)
target_link_libraries(SmartScanService INTERFACE smart)

target_link_libraries(main_file PUBLIC SmartScanService) 
target_link_libraries(main_file PUBLIC simpleble::simpleble)           
						 
