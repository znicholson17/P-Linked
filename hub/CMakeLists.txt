# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(hub)

#List of components the project depends on
set(EXTRA_COMPONENT_DIRS components)

# Add in custom custom components
list(APPEND EXTRA_COMPONENT_DIRS components/socket_server components/wifi)


