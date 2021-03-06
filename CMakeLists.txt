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

set(QTWC_QTDIR "" CACHE STRING "Qt install path")


if("${QTWC_QTDIR}" STREQUAL "")
	message(FATAL_ERROR "QTWC_QTDIR variable not set! Define with -QTWC_QTDIR:String=[PATH_TO_QT]")
endif()

list(APPEND CMAKE_PREFIX_PATH ${QTWC_QTDIR})

# Find the necessary Qt5 modules
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5QuickWidgets REQUIRED)

# Test for supported Qt version
find_program(QMAKE_EXECUTABLE NAMES qmake HINTS ${QTWC_QTDIR} ENV QTDIR PATH_SUFFIXES bin)
execute_process(COMMAND ${QMAKE_EXECUTABLE} -query QT_VERSION OUTPUT_VARIABLE QT_VERSION)
if(QT_VERSION VERSION_LESS QT_MINIMUM_VERSION)
	MESSAGE(FATAL_ERROR "Minimum supported Qt version: ${QT_MINIMUM_VERSION}. Installed version: ${QT_VERSION}")
endif()

# Target definition
# ==================================================

set(SOURCES
		source/FPSlider.cpp
		source/FancySlider.cpp
		source/RangeBase.cpp
		source/IntRange.cpp
		source/DoubleRange.cpp
		source/RangeSlider.cpp
		source/OptionGrid.cpp
		source/ContextMenuEventWrapper.cpp
		source/Slider.cpp
		source/ProgressBar.cpp)

set(HEADERS
		include/QTWC/FPSlider.h
		include/QTWC/FancySlider.h
		include/QTWC/RangeBase.h
		include/QTWC/IntRange.h
		include/QTWC/DoubleRange.h
		include/QTWC/RangeSlider.h
		include/QTWC/OptionGrid.h
		include/QTWC/ContextMenuEventWrapper.h
		include/QTWC/Slider.h
		include/QTWC/ProgressBar.h)

add_library(${LIBRARY_NAME} ${SOURCES} ${HEADERS})

set_target_properties(${LIBRARY_NAME}
   PROPERTIES
     AUTOMOC TRUE
     AUTOUIC TRUE
     CMAKE_INCLUDE_CURRENT_DIR TRUE)

set(RANGE_SLIDER_HORIZONTAL_QML_PATH ${CMAKE_CURRENT_SOURCE_DIR}/QML/HorizontalRangeSlider.qml)
set(RANGE_SLIDER_VERTICAL_QML_PATH ${CMAKE_CURRENT_SOURCE_DIR}/QML/VerticalRangeSlider.qml)
set(OPTION_GRID_QML_PATH ${CMAKE_CURRENT_SOURCE_DIR}/QML/SwitchWithId.qml)
set(SLIDER_HORIZONTAL_QML_PATH ${CMAKE_CURRENT_SOURCE_DIR}/QML/HorizontalSlider.qml)
set(HORIZONTAL_PROGRESS_BAR_QML_PATH ${CMAKE_CURRENT_SOURCE_DIR}/QML/HorizontalProgressBar.qml)
configure_file (
		"configure/QMLPaths.h.in"
		"${CMAKE_CURRENT_BINARY_DIR}/include/QMLPaths.h"
)

target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(${LIBRARY_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)

target_link_libraries(${LIBRARY_NAME} PUBLIC Qt5::Core Qt5::Widgets Qt5::QuickWidgets)