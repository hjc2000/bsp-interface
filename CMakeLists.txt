cmake_minimum_required(VERSION 3.20)
include($ENV{cpp_lib_build_scripts_path}/cmake-module/setup.cmake)
include(target_import_boost)
include(target_import_nlohmann_json)
include(target_import_base)

set(ProjectName bsp-interface)
project(${ProjectName})
enable_language(ASM)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)

add_library(${ProjectName} STATIC)
target_import_src(${ProjectName})
target_import_boost(${ProjectName} PUBLIC)
target_import_nlohmann_json(${ProjectName} PUBLIC)
target_import_base(${ProjectName} PUBLIC)

set(CMAKE_INSTALL_PREFIX $ENV{cpp_lib_build_scripts_path}/${platform}/.libs/${ProjectName}/)
