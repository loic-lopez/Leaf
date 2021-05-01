cmake_minimum_required(VERSION 3.17)
project(Leaf LANGUAGES CXX VERSION "0.0.1")

set(CMAKE_CXX_STANDARD 20)

add_definitions(-DUSE32bit=false)
add_definitions(-DCMAKE_GENERATOR_PLATFORM=x64)

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
    add_compile_options(/W4 /WX)
elseif (CMAKE_COMPILER_IS_GNUCXX)
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif ()

if (NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(SEND_ERROR "Please switch to x64 build.")
    return()
endif ()

# Download automatically, you can also just copy the conan.cmake file
if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.16.1/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake"
            TLS_VERIFY ON)
endif ()

include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_cmake_run(
        CONANFILE
        conanfile.txt
        BASIC_SETUP
        BUILD missing
        SETTINGS compiler.cppstd=17
)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

include_directories(app/leaf/include)

add_subdirectory(app)
add_subdirectory(conf)