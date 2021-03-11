cmake_minimum_required(VERSION 3.16)

project(taglib-helper LANGUAGES CXX)
cmake_policy(SET CMP0087 NEW)
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

include(CPack)