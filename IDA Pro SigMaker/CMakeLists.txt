set(PROJECT_NAME IDAProSigMaker)

################################################################################
# Source groups
################################################################################
set(Headerdateien
    "Main.h"
    "Version.h"
)
source_group("Headerdateien" FILES ${Headerdateien})

set(Plugin
    "Plugin.cpp"
    "Plugin.h"
)
source_group("Plugin" FILES ${Plugin})

set(Quelldateien
    "Main.cpp"
)
source_group("Quelldateien" FILES ${Quelldateien})

set(SignatureUtils
    "SignatureUtils.cpp"
    "SignatureUtils.h"
)
source_group("SignatureUtils" FILES ${SignatureUtils})

set(Utils
    "Utils.cpp"
    "Utils.h"
)
source_group("Utils" FILES ${Utils})

set(ALL_FILES
    ${Headerdateien}
    ${Plugin}
    ${Quelldateien}
    ${SignatureUtils}
    ${Utils}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
################################################################################
# Includes for CMake from *.props
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    use_props(${PROJECT_NAME} IDAPlugin32Bit "MainProperties.cmake")
    use_props(${PROJECT_NAME} IDAPlugin64Bit "MainProperties.cmake")
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    use_props(${PROJECT_NAME} IDAPlugin32Bit "MainProperties.cmake")
    use_props(${PROJECT_NAME} IDAPlugin64Bit "MainProperties.cmake")
endif()

set(ROOT_NAMESPACE IDAProSigMaker)

################################################################################
# Target name
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_IDAPLUGIN32BIT "SigMaker"
        TARGET_NAME_IDAPLUGIN64BIT "SigMaker64"
    )
endif()
################################################################################
# Output directory
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_IDAPLUGIN32BIT "${CMAKE_SOURCE_DIR}/${CMAKE_VS_PLATFORM_NAME}/"
        OUTPUT_DIRECTORY_IDAPLUGIN64BIT "${CMAKE_SOURCE_DIR}/${CMAKE_VS_PLATFORM_NAME}/"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION                "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION                "TRUE"
    )
endif()
################################################################################
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
        MultiThreadedDLL
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
        MultiThreaded
    )
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../SDK/include"
    )
endif()

################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:IDAPlugin64Bit>:"
            "__EA64__"
        ">"
        "__NT__;"
        "_MBCS"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "_MBCS"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:IDAPlugin32Bit>:
                /sdl-
            >
            $<$<CONFIG:IDAPlugin64Bit>:
                /sdl;
                /wd4996
            >
            /permissive-;
            /MP;
            /std:c++latest;
            /O2;
            /Oi;
            /Gy;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            /permissive-;
            /O2;
            /Oi;
            /sdl;
            /Gy;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            /OPT:REF;
            /OPT:ICF;
            /EXPORT:PLUGIN
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            /OPT:REF;
            /OPT:ICF
        )
    endif()
endif()

################################################################################
# Dependencies
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "ida"
    )
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_link_directories(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:IDAPlugin32Bit>:"
            "${CMAKE_CURRENT_SOURCE_DIR}/../SDK/lib/x64_win_vc_32_pro"
        ">"
        "$<$<CONFIG:IDAPlugin64Bit>:"
            "${CMAKE_CURRENT_SOURCE_DIR}/../SDK/lib/x64_win_vc_64_pro"
        ">"
    )
endif()



























set(PROJECT_NAME IDAProSigMaker)

################################################################################
# Source groups
################################################################################
set(Headerdateien
    "Main.h"
    "Version.h"
)
source_group("Headerdateien" FILES ${Headerdateien})

set(Plugin
    "Plugin.cpp"
    "Plugin.h"
)
source_group("Plugin" FILES ${Plugin})

set(Quelldateien
    "Main.cpp"
)
source_group("Quelldateien" FILES ${Quelldateien})

set(SignatureUtils
    "SignatureUtils.cpp"
    "SignatureUtils.h"
)
source_group("SignatureUtils" FILES ${SignatureUtils})

set(Utils
    "Utils.cpp"
    "Utils.h"
)
source_group("Utils" FILES ${Utils})

set(ALL_FILES
    ${Headerdateien}
    ${Plugin}
    ${Quelldateien}
    ${SignatureUtils}
    ${Utils}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
################################################################################
# Includes for CMake from *.props
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    use_props(${PROJECT_NAME} IDAPlugin32Bit "MainProperties.cmake")
    use_props(${PROJECT_NAME} IDAPlugin64Bit "MainProperties.cmake")
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    use_props(${PROJECT_NAME} IDAPlugin32Bit "MainProperties.cmake")
    use_props(${PROJECT_NAME} IDAPlugin64Bit "MainProperties.cmake")
endif()

set(ROOT_NAMESPACE IDAProSigMaker)

################################################################################
# Target name
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_IDAPLUGIN32BIT "SigMaker"
        TARGET_NAME_IDAPLUGIN64BIT "SigMaker64"
    )
endif()
################################################################################
# Output directory
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_IDAPLUGIN32BIT "${CMAKE_SOURCE_DIR}/${CMAKE_VS_PLATFORM_NAME}/"
        OUTPUT_DIRECTORY_IDAPLUGIN64BIT "${CMAKE_SOURCE_DIR}/${CMAKE_VS_PLATFORM_NAME}/"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION                "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION                "TRUE"
    )
endif()
################################################################################
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
        MultiThreadedDLL
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
        MultiThreaded
    )
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../SDK/include"
    )
endif()

################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:IDAPlugin64Bit>:"
            "__EA64__"
        ">"
        "__NT__;"
        "_MBCS"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "_MBCS"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:IDAPlugin32Bit>:
                /sdl-
            >
            $<$<CONFIG:IDAPlugin64Bit>:
                /sdl;
                /wd4996
            >
            /permissive-;
            /MP;
            /std:c++latest;
            /O2;
            /Oi;
            /Gy;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            /permissive-;
            /O2;
            /Oi;
            /sdl;
            /Gy;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            /OPT:REF;
            /OPT:ICF;
            /EXPORT:PLUGIN
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            /OPT:REF;
            /OPT:ICF
        )
    endif()
endif()

################################################################################
# Dependencies
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "ida"
    )
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_link_directories(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:IDAPlugin32Bit>:"
            "${CMAKE_CURRENT_SOURCE_DIR}/../SDK/lib/x64_win_vc_32_pro"
        ">"
        "$<$<CONFIG:IDAPlugin64Bit>:"
            "${CMAKE_CURRENT_SOURCE_DIR}/../SDK/lib/x64_win_vc_64_pro"
        ">"
    )
endif()

