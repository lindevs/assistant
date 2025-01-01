include(FindPackageHandleStandardArgs)

find_path(stable_diffusion_INCLUDE_DIRS REQUIRED NAMES stable-diffusion.h)
find_library(stable_diffusion_LIBRARY REQUIRED NAMES stable-diffusion)

add_library(stable_diffusion SHARED IMPORTED)
set_target_properties(stable_diffusion PROPERTIES IMPORTED_LOCATION ${stable_diffusion_LIBRARY})
if (WIN32)
    set_target_properties(stable_diffusion PROPERTIES IMPORTED_IMPLIB ${stable_diffusion_LIBRARY})
endif ()

add_library(SD::SD INTERFACE IMPORTED)
set_property(TARGET SD::SD PROPERTY INTERFACE_LINK_LIBRARIES stable_diffusion)

find_package_handle_standard_args(SD::SD DEFAULT_MSG stable_diffusion_LIBRARY)
