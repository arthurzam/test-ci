cmake_minimum_required(VERSION 3.16)

project(taglib-helper LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")


find_package(TAGLIB REQUIRED)
include_directories(${TAGLIB_INCLUDE_DIRS})
link_directories(${TAGLIB_LIBRARY_DIRS})
add_definitions(-DTAGLIB_FULL_INCLUDE_PATH)
set(CMAKE_SHARED_MODULE_PREFIX "")

message(">>>> Libs: ${TAGLIB_LIBRARIES}")
message(">>>> include: ${TAGLIB_INCLUDE_DIRS}")

set(PROJECT_SOURCES
        main.cpp
)

add_library(${PROJECT_NAME} MODULE
    ${PROJECT_SOURCES}
)

target_link_libraries(taglib-helper PRIVATE ${TAGLIB_LIBRARIES})
install(TARGETS taglib-helper DESTINATION bin)
x_vcpkg_install_local_dependencies(taglib-helper)