message("-- Linking SmartScanService")

##Set the location files
set(H_files 			${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(S_files 			${CMAKE_CURRENT_SOURCE_DIR}/src)

#If you ever add new files for your project, make sure to include them here, so that cmake can take this into account when building the new .lib file when you run it
set(SOURCES ${S_files}/CSVExport.cpp
            ${S_files}/DataAcquisition.cpp
            ${S_files}/Point3.cpp
            ${S_files}/Scan.cpp
            ${S_files}/SmartScanService.cpp
            ${S_files}/TrakStarController.cpp
            ${S_files}/Trigger.cpp 
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
            ${H_files}/Trigger.h)
			
		 

set(simpleble 	${CMAKE_CURRENT_SOURCE_DIR}/../simpleble_install/simpleble)
add_subdirectory(${simpleble}	  ${CMAKE_CURRENT_BINARY_DIR}/../simpleble)#Looks for the CMakelists.txt file for simpleble

add_library(SmartScanService STATIC  ${SOURCES})#This line uses the file list above and compiles it into a library, that later is linked with SmartScanService and the main SmartScan Project.
target_link_libraries(SmartScanService PRIVATE simpleble::simpleble)    #SmartScanService also uses the ble library, so the link is done between the two here aswell.	