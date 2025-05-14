cmake_minimum_required(VERSION 3.18)
project(ComPortTools)

set(CMAKE_CXX_STANDARD 17)
set(TARGET ComPortTools)

option(CASE_INSENSITIVE "Case insensitive method names" ON) #Имена методов без учета регистра
option(STATIC_CRT "Static CRT linkage" OFF) #Это флаг, который указывает, что проект должен линковаться со статической версией стандартной библиотеки C/C++ (CRT — C Runtime Library), а не с динамической (DLL).
option(OUT_PARAMS "Support output parameters" OFF) # Поддержка выходных параметров

list(APPEND SOURCES
        src/addin.def
        src/stdafx.h
        src/dllmain.cpp
        src/exports.cpp
        src/Component.cpp
        src/Component.h
        src/ComPortTools.cpp
        src/ComPortTools.h
	src/xserial.cpp
        src/xserial.hpp
	src/str_switch.h)

if (DEBUG_APP STREQUAL 1)

list(APPEND SOURCES
        src/test_app.cpp)

add_executable(${TARGET} ${SOURCES})
target_include_directories(${TARGET} PRIVATE
        include)

else()

add_library(${TARGET} SHARED
        ${SOURCES})

target_compile_definitions(${TARGET} PRIVATE
        UNICODE
        _UNICODE)

if (CASE_INSENSITIVE)
    target_compile_definitions(${TARGET} PRIVATE CASE_INSENSITIVE)
endif ()

if (OUT_PARAMS)
    target_compile_definitions(${TARGET} PRIVATE OUT_PARAMS)
endif ()

target_include_directories(${TARGET} PRIVATE
        include)

if (WIN32)
    if (STATIC_CRT)
        string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
        string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    endif ()
    target_compile_definitions(${TARGET} PRIVATE
            _WINDOWS
            _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING)
    target_compile_options(${TARGET} PRIVATE /utf-8)
endif ()

if (UNIX)

    if (WIN32_COMPILE_LINUX STREQUAL 1)
       message(STATUS "Win32 compile linux on")
       
       add_definitions(-DWIN32_COMPILE_LINUX)
       
       # specify the cross compiler
       set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
       set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
       set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)

       set(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32)

       # search for programs in the build host directories
       set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
       # for libraries and headers in the target directories
       set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
       set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

    endif()
    
    if (TARGET_ARCH STREQUAL "x86")
        set(CMAKE_C_FLAGS "-m32 ${CMAKE_C_FLAGS}")
        set(CMAKE_CXX_FLAGS "-m32 ${CMAKE_CXX_FLAGS}")
    endif ()


    add_custom_target(
	package
    	COMMAND zip -j build/ComPortTools_Componenta.zip MANIFEST.XML build/lib${TARGET}.so
    	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    	DEPENDS ${TARGET}
	)



endif ()

endif ()
