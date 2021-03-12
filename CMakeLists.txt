cmake_minimum_required(VERSION 3.16)

project(taglib-helper LANGUAGES CXX)
cmake_policy(SET CMP0087 NEW)
SET(X_VCPKG_APPLOCAL_DEPS_INSTALL ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")


find_package(TAGLIB REQUIRED)
include_directories(${TAGLIB_INCLUDE_DIRS})
link_directories(${TAGLIB_LIBRARY_DIRS})
add_definitions(-DTAGLIB_FULL_INCLUDE_PATH)
set(CMAKE_SHARED_MODULE_PREFIX "")

set(PROJECT_SOURCES
        main.cpp
)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
)

target_link_libraries(taglib-helper PRIVATE ${TAGLIB_LIBRARIES})
install(TARGETS taglib-helper DESTINATION bin)
#x_vcpkg_install_local_dependencies(TARGETS taglib-helper DESTINATION bin)

#add_custom_target(InstallDLLs
#      COMMAND powershell -noprofile -executionpolicy Bypass -file ${Z_VCPKG_TOOLCHAIN_DIR}/msbuild/applocal.ps1
#      -targetBinary ${CMAKE_INSTALL_PREFIX}/bin/taglib-helper.exe
#      -installedDir "${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}$<$<CONFIG:Debug>:/debug>/bin"
#      -OutVariable out
#  )
#  set_target_properties(InstallDLLs PROPERTIES EXCLUDE_FROM_ALL TRUE)
  # runs this target after installation
#  install(CODE "execute_process(COMMAND \"${CMAKE_COMMAND}\" --build . --target InstallDLLs --config RELEASE)")
message(">>>> Path: $ENV{PATH}")
install (CODE "
	execute_process(COMMAND \"${Z_VCPKG_POWERSHELL_PATH}\" -noprofile -executionpolicy Bypass -file ${Z_VCPKG_TOOLCHAIN_DIR}/msbuild/applocal.ps1
					-targetBinary \${CMAKE_INSTALL_PREFIX}/bin/taglib-helper.exe
                    -installedDir \"${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}$<$<CONFIG:Debug>:/debug>/bin\"
					-OutVariable out)
")
  
include(CPack)
