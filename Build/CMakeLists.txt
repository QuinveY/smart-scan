message("-- Linking ATLIB")
add_library(ATC3DG64 SHARED ATC3DG64.DLL) #Turns the .dll file into a library that can be linked to the main project.
set_target_properties(ATC3DG64 PROPERTIES LINKER_LANGUAGE C) #Specify the linker language that Cmake requires.