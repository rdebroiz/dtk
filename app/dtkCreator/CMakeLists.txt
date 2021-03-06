### CMakeLists.txt ---
##
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Aug  3 17:34:51 2009 (+0200)
## Version: $Id$
## Last-Updated: Fri Apr 27 21:31:54 2012 (+0200)
##           By: Julien Wintz
##     Update #: 171
######################################################################
##
### Commentary:
##
######################################################################
##
### Change log:
##
######################################################################

project(dtkCreator)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkCreatorMainWindow.h
  dtkCreatorMainWindow_p.h)

set(${PROJECT_NAME}_SOURCES
  dtkCreatorMainWindow.cpp
  main.cpp)

if(APPLE)
set(${PROJECT_NAME}_SOURCES
  ${${PROJECT_NAME}_SOURCES}
  dtkCreatorMainWindow.mm)
endif(APPLE)

set(${PROJECT_NAME}_RESOURCES
  dtkCreator.qrc)

## #################################################################
## Build rules
## #################################################################

if(NOT MSVC)
add_definitions(-Wno-write-strings)
endif(NOT MSVC)

qt5_add_RESOURCES(${PROJECT_NAME}_SOURCES_QRC ${${PROJECT_NAME}_RESOURCES})

add_executable(${PROJECT_NAME} MACOSX_BUNDLE WIN32
  ${${PROJECT_NAME}_SOURCES_QRC}
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS})


target_link_libraries(${PROJECT_NAME}
  dtkLog
  dtkCore
  dtkComposer
  dtkGuiSupport
  dtkWidgets)

if(DTK_BUILD_SUPPORT_PLOT)
  target_link_libraries(${PROJECT_NAME} dtkPlotSupport)
endif(DTK_BUILD_SUPPORT_PLOT)

if(APPLE)
target_link_libraries(${PROJECT_NAME}
  "-framework Cocoa")
endif(APPLE)

target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

## #################################################################
## Source file layout in development environments like Visual Studio
## #################################################################

SOURCE_GROUP("Header Files" REGULAR_EXPRESSION .*\\.h\$)
SOURCE_GROUP("Generated Files" FILES ${${PROJECT_NAME}_SOURCES_MOC})

## #################################################################
## Installation
## #################################################################

install(FILES ${${PROJECT_NAME}_MODULES} DESTINATION modules)
install(TARGETS ${PROJECT_NAME}
   BUNDLE DESTINATION bin
  RUNTIME DESTINATION bin)
