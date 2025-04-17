cmake_minimum_required(VERSION 3.16)

# Project name and language
project(IDAProSigMaker VERSION 1.0 LANGUAGES CXX)

# Force C++23 standard for std::expected, std::ranges, etc.
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Subdirectory containing source files (supports spaces)
set(SRC_SUBDIR "IDA Pro SigMaker")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/${SRC_SUBDIR}")

# Detect platform and set IDA SDK paths
if(UNIX)
    set(IDASDK_ROOT "/SDK" CACHE PATH "Path to IDA SDK")
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
else()
    set(CMAKE_SYSTEM_VERSION 10.0)
endif()

message("Using source directory: ${SRC_DIR}")

# Handle Visual Studio platform name on UNIX
if(NOT CMAKE_VS_PLATFORM_NAME AND UNIX)
    set(CMAKE_VS_PLATFORM_NAME "x64")
endif()
message("${CMAKE_VS_PLATFORM_NAME} architecture in use")

# Configuration types (for multi-config generators like VS)
set(CMAKE_CONFIGURATION_TYPES "IDAPlugin32Bit;IDAPlugin64Bit" CACHE STRING "" FORCE)

# Platform-specific settings
if(MSVC)
    # Windows compiler flags
    add_compile_options(/W3 /MP /O2 /GL)
    add_link_options(/LTCG)
else()  # UNIX
    # Linux compiler & linker flags
    add_compile_options(-fPIC -fvisibility=hidden)
    add_link_options(-shared)

    # Determine 32 vs 64-bit based on pointer size
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(ARCH_DIR "x64_linux_gcc_64")
        # __EA64__ comes from CMake, plugin.h handles __LINUX__
        add_compile_definitions(__EA64__=1)
    else()
        set(ARCH_DIR "x86_linux")
    endif()

    set(IDASDK_INCLUDE_DIR "${IDASDK_ROOT}/include")
    set(IDASDK_LIB_DIR     "${IDASDK_ROOT}/lib/${ARCH_DIR}")
endif()

# List of plugin source files in the external directory
set(SIGMAKER_SOURCES
    "${SRC_DIR}/Main.cpp"
    "${SRC_DIR}/Plugin.cpp"
    "${SRC_DIR}/SignatureUtils.cpp"
    "${SRC_DIR}/Utils.cpp"
)

# Define the shared library target
add_library(SigMaker SHARED ${SIGMAKER_SOURCES})

target_include_directories(SigMaker PRIVATE ${IDASDK_INCLUDE_DIR})
target_link_directories(SigMaker PRIVATE ${IDASDK_LIB_DIR})

if(UNIX)
    target_link_libraries(SigMaker PRIVATE
  "${CMAKE_SOURCE_DIR}/libida.so"
)

endif()

# Output naming and properties
if(UNIX)
    set_target_properties(SigMaker PROPERTIES
        OUTPUT_NAME "SigMaker64"
        PREFIX ""
        SUFFIX ".so"
    )
else()
    set_target_properties(SigMaker PROPERTIES
        OUTPUT_NAME "SigMaker${CMAKE_VS_PLATFORM_NAME}"
    )
endif()

# Install rules for Linux
if(UNIX)
    install(TARGETS SigMaker
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )
endif()
