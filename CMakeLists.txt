# Usage
# ==================================================
# add_subdirectory(QTWC)
# target_link_libraries(YOUR_TARGET QTWC)

# in source:
# #include "QTWC/FPSlider.h"

# Project Setup
# ==================================================

cmake_minimum_required(VERSION 3.17.1)

set(LIBRARY_NAME QTWC)

project(${LIBRARY_NAME} 
    DESCRIPTION "QTWC - A collection of Qt Widgets."
    HOMEPAGE_URL "https://github.com/truenicfel/QTWC" 
    LANGUAGES CXX)

# QT
# ==================================================

set(QT_MINIMUM_VERSION 5.9.0)

if(NOT DEFINED ENV{QTDIR})
	MESSAGE(STATUS "QTDIR environment variable not set. Be sure to set the QTDIR
	cmake cache variable to the Qt root install location")
endif()

set(QTDIR $ENV{QTDIR} CACHE STRING "Qt install path")
list(APPEND CMAKE_PREFIX_PATH ${QTDIR})

# Find the necessary Qt5 modules
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

# Test for supported Qt version
find_program(QMAKE_EXECUTABLE NAMES qmake HINTS ${QTDIR} ENV QTDIR PATH_SUFFIXES bin)
execute_process(COMMAND ${QMAKE_EXECUTABLE} -query QT_VERSION OUTPUT_VARIABLE QT_VERSION)
if(QT_VERSION VERSION_LESS QT_MINIMUM_VERSION)
	MESSAGE(FATAL_ERROR "Minimum supported Qt version: ${QT_MINIMUM_VERSION}. Installed version: ${QT_VERSION}")
endif()

# Target definition
# ==================================================

set(SOURCES
    source/FPSlider.cpp
    source/FancySlider.cpp
    )

set(HEADERS
    include/QTWC/FPSlider.h
    include/QTWC/FancySlider.h
    )

add_library(${LIBRARY_NAME} ${SOURCES} ${HEADERS})

set_target_properties(${LIBRARY_NAME}
   PROPERTIES
     AUTOMOC TRUE
     AUTOUIC TRUE
     CMAKE_INCLUDE_CURRENT_DIR TRUE)

target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${LIBRARY_NAME} PUBLIC Qt5::Core Qt5::Widgets)