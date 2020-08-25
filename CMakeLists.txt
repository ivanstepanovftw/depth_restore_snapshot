cmake_minimum_required(VERSION 3.16)

project(untitled VERSION 1.0 LANGUAGES CXX)

set(TARGET DOM)
add_executable(${TARGET} main.cpp)
set_property(TARGET ${TARGET} PROPERTY CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
if (NOT MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pie")
    target_compile_options(${TARGET} PUBLIC -fstack-protector)
    target_compile_definitions(${TARGET} PUBLIC
            -D_FORTIFY_SOURCE=2
            )
    target_link_options(${TARGET} PUBLIC
            "LINKER:SHELL:-z defs"
            "LINKER:SHELL:-z relro -z now"
            )

    target_compile_options(${TARGET} PUBLIC
            -O3
            )
    target_compile_options(${TARGET} PUBLIC "$<$<STREQUAL:${CMAKE_CXX_COMPILER_ID},Intel>:-mtune=native;-march=native;-xHOST>")
    target_compile_options(${TARGET} PUBLIC "$<$<STREQUAL:${CMAKE_CXX_COMPILER_ID},GNU>:-mtune=native;-march=native>")
    target_compile_options(${TARGET} PUBLIC "$<$<STREQUAL:${CMAKE_CXX_COMPILER_ID},Clang>:-mtune=native;-march=native>")  # TODO[med] is mtune implemented in Clang?

    target_compile_options(${TARGET} PUBLIC
            -Wall -Wextra
            -Wno-unused
            -Wconversion -Wsign-conversion
            -Wformat
            #[[GNU,Clang]] "$<$<NOT:$<STREQUAL:${CMAKE_CXX_COMPILER_ID},Intel>>:-Wpedantic>"
            #[[GNU,Clang]] "$<$<NOT:$<STREQUAL:${CMAKE_CXX_COMPILER_ID},Intel>>:-Wstack-protector>"
            )
    target_compile_options(${TARGET} PUBLIC
            -Werror=format-security
            -Werror=return-type
            )
    target_compile_options(${TARGET} PUBLIC
            -Werror
            )
else()
    target_compile_options(${TARGET} PUBLIC
            /Ox
            )
endif()

target_include_directories(${TARGET} PUBLIC
        include
        )

#target_link_libraries(${TARGET} PUBLIC
#        )

#include(PVS-Studio.cmake)
#pvs_studio_add_target(TARGET ${TARGET}.analyze ALL
#        OUTPUT FORMAT errorfile
#        ANALYZE ${TARGET}
#        MODE GA:1,2,3 OP
#        LOG target.err
#        )
