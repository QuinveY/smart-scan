set(ATC3DG64 D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/smart_scan_reformatted/lib_ATC3DG64)
target_include_directories(main_file PRIVATE ${ATC3DG64})

set(LIBAT D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/smart_scan_reformatted/lib_ATC3DG64/ATC3DG64.lib)
set(SMARTS D:/Smart_Glove_Project/Temp_folder/smart-scan/cmake_build/smart_scan_reformatted/lib_ATC3DG64/ATC3DG64.lib/SmartScanService.lib)


			add_library(atlib STATIC IMPORTED)
set_property(TARGET atlib PROPERTY
             IMPORTED_LOCATION ${LIBAT})
			 
			add_library(smart STATIC IMPORTED)
set_property(TARGET smart PROPERTY
             IMPORTED_LOCATION ${SMARTS})
			 
