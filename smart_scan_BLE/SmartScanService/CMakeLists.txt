##Set the location files
set(H_files 			${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(S_files 			${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SOURCES ${S_files}/CSVExport.cpp
            ${S_files}/DataAcquisition.cpp
            ${S_files}/Point3.cpp
            ${S_files}/Scan.cpp
            ${S_files}/SmartScanService.cpp
            ${S_files}/TrakStarController.cpp
            ${S_files}/Trigger.cpp 
            ${S_files}/BLEController.cpp 
			${H_files}/DirDef.h
            ${H_files}/ATC3DG.h
            ${H_files}/CSVExport.h
			${H_files}/ini.h
            ${H_files}/DataAcquisition.h
            ${H_files}/Exceptions.h
            ${H_files}/Point3.h
            ${H_files}/Scan.h
            #${H_files}/SmartScanConfig.h #Included in the main project
            ${H_files}/TrakStarController.h
            ${H_files}/SmartScanService.h
            ${H_files}/Trigger.h
            ${H_files}/BLEController.h)

set(simpleble 			${CMAKE_CURRENT_SOURCE_DIR}/../simpleble_install/simpleble)
add_subdirectory(${simpleble}	  ${CMAKE_CURRENT_BINARY_DIR}/../simpleble)

add_library(SmartScanService STATIC  ${SOURCES})	
target_link_libraries(SmartScanService PRIVATE simpleble::simpleble)    