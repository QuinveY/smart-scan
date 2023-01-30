message("-- Linking ATLIB")
add_library(ATC3DG64 SHARED ATC3DG64.DLL)
set_target_properties(ATC3DG64 PROPERTIES LINKER_LANGUAGE C)