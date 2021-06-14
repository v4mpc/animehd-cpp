cmake_minimum_required(VERSION 3.19)
project(animehd)
set(CMAKE_CXX_STANDARD 14)
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)
link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
add_executable(animehd main.cpp MainWindow.cpp MainWindow.h utils.cpp utils.h)
target_link_libraries(animehd ${GTKMM_LIBRARIES} ${CONAN_LIBS})


