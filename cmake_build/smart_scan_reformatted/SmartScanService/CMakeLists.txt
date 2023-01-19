set(H_files D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/smart_scan_reformatted/SmartScanService/smartscan_inc)
set(S_files D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/smart_scan_reformatted/SmartScanService/smartscan_src)
set(SOURCES ${S_files}/CSVExport.cpp
            ${S_files}/DataAcquisition.cpp
            ${S_files}/Point3.cpp
            ${S_files}/Scan.cpp
            ${S_files}/SmartScanService.cpp
            ${S_files}/TrakStarController.cpp
            ${S_files}/Trigger.cpp 

            ${H_files}/ATC3DG.h
            ${H_files}/CSVExport.h
            ${H_files}/DataAcquisition.h
            ${H_files}/Exceptions.h
            ${H_files}/Point3.h
            ${H_files}/Scan.h
            ${H_files}/SmartScanConfig.h
            ${H_files}/TrakStarController.h
            ${H_files}/SmartScanService.h
            ${H_files}/Trigger.h)

add_library(SmartScanService ${SOURCES})