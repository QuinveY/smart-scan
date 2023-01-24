message("-- Linking ATLIB")
add_library(atlib STATIC ATC3DG64.DLL)
set_target_properties(atlib PROPERTIES LINKER_LANGUAGE C)