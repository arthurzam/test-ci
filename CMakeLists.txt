cmake_minimum_required(VERSION 3.16)

project(taglib-helper LANGUAGES CXX C)
#SET(X_VCPKG_APPLOCAL_DEPS_INSTALL ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

file(TO_CMAKE_PATH "$ENV{PATH}" MyPath)
install (CODE "set(ENV{PATH} \"${MyPath}\")" )


find_package(TAGLIB REQUIRED)
add_definitions(-DTAGLIB_FULL_INCLUDE_PATH -DTAGLIB_STATIC)
set(CMAKE_SHARED_MODULE_PREFIX "")

add_executable(taglib-helper
    "main.cpp"
)
target_link_libraries(taglib-helper PRIVATE PkgConfig::TAGLIB)
set_property(TARGET taglib-helper PROPERTY
  MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
install(TARGETS taglib-helper DESTINATION bin)


find_package(PNG REQUIRED)
add_executable(magic-png
    "png.c"
)
target_link_libraries(magic-png PRIVATE PNG::PNG)
set_property(TARGET magic-png PROPERTY
  MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
install(TARGETS magic-png DESTINATION bin/modules)

install (CODE "
	execute_process(COMMAND \"${Z_VCPKG_POWERSHELL_PATH}\" -noprofile -executionpolicy Bypass -file ${Z_VCPKG_TOOLCHAIN_DIR}/msbuild/applocal.ps1
					-targetBinary \${CMAKE_INSTALL_PREFIX}/bin/taglib-helper.exe
                    -installedDir \"${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}$<$<CONFIG:Debug>:/debug>/bin\"
					-OutVariable out)
")
install (CODE "
	execute_process(COMMAND \"${Z_VCPKG_POWERSHELL_PATH}\" -noprofile -executionpolicy Bypass -file ${Z_VCPKG_TOOLCHAIN_DIR}/msbuild/applocal.ps1
					-targetBinary \${CMAKE_INSTALL_PREFIX}/bin/modules/magic-png.exe
                    -installedDir \"${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}$<$<CONFIG:Debug>:/debug>/bin\"
					-OutVariable out)
")
  
include(CPack)
