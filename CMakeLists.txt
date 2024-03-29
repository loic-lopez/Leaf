cmake_minimum_required(VERSION 3.17)

if (DEFINED ENV{semVer})
    set(GIT_VERSION ENV{semVer})
else()
    string(TIMESTAMP GIT_VERSION "%Y.%m.%d")
endif()

message(STATUS "Found version ${GIT_VERSION}")

project(Leaf LANGUAGES CXX VERSION ${GIT_VERSION})

set(CMAKE_CXX_STANDARD 20)

add_definitions(-DUSE32bit=false)
add_definitions(-DCMAKE_GENERATOR_PLATFORM=x64)
## Set variables for libraries
# as for now std::format is not available
# add_definitions(-DSPDLOG_USE_STD_FORMAT=ON)

if (NOT EXISTS ${CMAKE_BINARY_DIR}/CMakeCache.txt)
    if (NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
    endif ()
endif ()

if (WIN32)
    macro(get_WIN32_WINNT version)
        if (CMAKE_SYSTEM_VERSION)
            set(ver ${CMAKE_SYSTEM_VERSION})
            string(REGEX MATCH "^([0-9]+).([0-9])" ver ${ver})
            string(REGEX MATCH "^([0-9]+)" verMajor ${ver})
            # Check for Windows 10, b/c we'll need to convert to hex 'A'.
            if ("${verMajor}" MATCHES "10")
                set(verMajor "A")
                string(REGEX REPLACE "^([0-9]+)" ${verMajor} ver ${ver})
            endif ()
            # Remove all remaining '.' characters.
            string(REPLACE "." "" ver ${ver})
            # Prepend each digit with a zero.
            string(REGEX REPLACE "([0-9A-Z])" "0\\1" ver ${ver})
            set(${version} "0x${ver}")
        endif ()
    endmacro()

    get_WIN32_WINNT(ver)
    add_definitions(-D_WIN32_WINNT=${ver})
endif ()

if (MSVC)
    add_compile_options(/W4 /WX /arch:AVX2)
    add_compile_options(/wd4455) # ignore warning C4455: 'operator ""sv': literal suffix identifiers that do not start with an underscore are reserved
elseif (CMAKE_COMPILER_IS_GNUCXX)
    # lots of warnings and all warnings as errors
    add_definitions(-D_FORTIFY_SOURCE=2)
    add_compile_options(
            -Wall -Wextra -pedantic -Werror
            -fexceptions # Enable table-based thread cancellation
            -fpie -Wl,-pie -fstack-protector-strong -Wl,-z,defs # ASLR
            -march=x86-64-v3 -m64 -mavx -ftree-vectorize # AVX and SSE
            -fno-math-errno -ffast-math
            -ftrivial-auto-var-init=zero # fill variables with 0x00 gcc-12 feature
    )
endif ()

if (NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(SEND_ERROR "Please switch to x64 build.")
    return()
endif ()

if (CMAKE_COMPILER_IS_GNUCC AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 12.1)
    message(FATAL_ERROR "Require at least gcc-12.1")
    return()
endif()

# Download automatically, you can also just copy the conan.cmake file
if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/0.18.1/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake"
            TLS_VERIFY ON)
endif ()




include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_cmake_run(
        CONANFILE
        conanfile.txt
        BASIC_SETUP
        BUILD missing
        SETTINGS compiler.cppstd=20
)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

include_directories(app/leaf/include)

# configure tests
enable_testing()

## Output dirs
if (NOT DEFINED LEAF_ROOT_PATH)
    set(LEAF_CONFIG_ROOT_PATH ${CMAKE_BINARY_DIR}/conf)
    set(LEAF_SERVERS_ROOT_PATH ${LEAF_CONFIG_ROOT_PATH})
    set(LEAF_LOG_DIR_ROOT_PATH ${CMAKE_BINARY_DIR}/log)
endif ()

if (DEFINED LEAF_ROOT_PATH)
    set(LEAF_CONFIG_ROOT_PATH ${LEAF_ROOT_PATH}/conf)
    set(LEAF_SERVERS_ROOT_PATH ${LEAF_CONFIG_ROOT_PATH})
    set(LEAF_LOG_DIR_ROOT_PATH ${LEAF_ROOT_PATH}/log)
endif ()

## Create base dirs
file(MAKE_DIRECTORY ${LEAF_LOG_DIR_ROOT_PATH})

# conf
add_subdirectory(conf)

# sources
add_subdirectory(app)
