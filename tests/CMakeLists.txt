include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.15.3
)
FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras) #Add it catch2 to cmake module path
include(Catch)

# 1. Find all immediate subdirectories
file(GLOB SUBDIRS LIST_DIRECTORIES true CONFIGURE_DEPENDS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)

# 2. Loop through each item found
foreach(DIR ${SUBDIRS})
    # Filter out files, keeping only actual directories
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${DIR})
        add_subdirectory(${DIR})

    endif()
endforeach()
