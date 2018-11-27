# see also: https://rix0r.nl/blog/2015/08/13/cmake-guide/
cmake_minimum_required(VERSION 3.3.2)
project(example)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(EXAMPLE_VERSION_MAJOR 0)
set(EXAMPLE_VERSION_MINOR 1)
set(EXAMPLE_VERSION_PATCH 0)
set(EXAMPLE_VERSION_STRING ${EXAMPLE_VERSION_MAJOR}.${EXAMPLE_VERSION_MINOR}.${EXAMPLE_VERSION_PATCH})

# Add FFTW library
set(findFFTW_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../findFFTW)
LIST(APPEND CMAKE_MODULE_PATH "${findFFTW_DIR}")
find_package(FFTW)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(${PROJECT_NAME} SHARED
    src/example.cpp
    )

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    )
    
set_target_properties(${PROJECT_NAME} PROPERTIES
    LANGUAGES CXX
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    VERSION ${EXAMPLE_VERSION_STRING}
    SOVERSION ${EXAMPLE_VERSION_MAJOR}
    PUBLIC_HEADER include/${PROJECT_NAME}/example.h
    )

set(ConfigPackageLocation "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

configure_package_config_file(
    ${PROJECT_NAME}Config.cmake.in
    ${PROJECT_NAME}Config.cmake                                            
    INSTALL_DESTINATION "${ConfigPackageLocation}"                       
    PATH_VARS CMAKE_INSTALL_PREFIX
    )
    
write_basic_package_version_file(
    ${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${EXAMPLE_VERSION_STRING}
    COMPATIBILITY AnyNewerVersion
    )

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Library
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Library
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}  COMPONENT Library # This is for Windows
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT Development
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME} COMPONENT Development
    )
# install(
#     DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
#     )

export(EXPORT ${PROJECT_NAME}Targets
  FILE
    ${PROJECT_NAME}Targets.cmake
  NAMESPACE
    ${PROJECT_NAME}::
)

install(EXPORT ${PROJECT_NAME}Targets
  FILE
    ${PROJECT_NAME}Targets.cmake
  NAMESPACE
    ${PROJECT_NAME}::
  DESTINATION
    ${ConfigPackageLocation}
  COMPONENT
    Development
)

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  DESTINATION
    ${ConfigPackageLocation}
  COMPONENT
    Development
)

