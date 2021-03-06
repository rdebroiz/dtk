## Version: $Id$
##
######################################################################
##
### Commentary:
##
######################################################################
##
### Change Log:
##
######################################################################
##
### Code:

string(SUBSTRING ${Qt5Core_VERSION_STRING} 0 3 Qt5_VERSION)

set(QT5_DOCUMENTATION_D "${QT5_BINARY_DIR}/../../../Docs/Qt-${Qt5_VERSION}")
set(QT5_QDOC_EXECUTABLE "${QT5_BINARY_DIR}/qdoc")
set(QT5_QHGN_EXECUTABLE "${QT5_BINARY_DIR}/qhelpgenerator")
set(DTK_QDOC_EXECUTABLE "${CMAKE_BINARY_DIR}/bin/dtkDoc")

message(STATUS "Using Qt5 binary dir: ${QT5_BINARY_DIR}")
message(STATUS "Using dtk binary doc: ${DTK_QDOC_EXECUTABLE}")
message(STATUS "Using Qt5 binary qhg: ${QT5_QDOC_EXECUTABLE}")

add_subdirectory("slides")

## ###################################################################
## dtk
## ###################################################################

configure_file(dtk/dtk.qdocconf.in ${CMAKE_CURRENT_BINARY_DIR}/dtkdoc.qdocconf IMMEDIATE @ONLY)

add_custom_target(dtk-doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${DTK_QDOC_EXECUTABLE} -no-link-errors dtkdoc.qdocconf)

## ###################################################################
## dtkMeta
## ###################################################################

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dtkMeta/dtkmeta.qdocconf.in ${CMAKE_CURRENT_BINARY_DIR}/dtkmeta.qdocconf IMMEDIATE @ONLY)

add_custom_target(dtkMeta-doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${DTK_QDOC_EXECUTABLE} dtkmeta.qdocconf
  COMMAND ${QT5_QHGN_EXECUTABLE} ${CMAKE_BINARY_DIR}/html/dtkmeta/dtkmeta.qhp -o ${CMAKE_BINARY_DIR}/html/dtkmeta.qch
  COMMENT "-- Generating dtkMeta documentation")

add_dependencies(dtkMeta-doc dtk-doc)

## ###################################################################
## dtkLog
## ###################################################################

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dtkLog/dtklog.qdocconf.in ${CMAKE_CURRENT_BINARY_DIR}/dtklog.qdocconf IMMEDIATE @ONLY)

add_custom_target(dtkLog-doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${DTK_QDOC_EXECUTABLE} dtklog.qdocconf
  COMMAND ${QT5_QHGN_EXECUTABLE} ${CMAKE_BINARY_DIR}/html/dtklog/dtklog.qhp -o ${CMAKE_BINARY_DIR}/html/dtklog.qch
  COMMENT "-- Generating dtkLog documentation")

add_dependencies(dtkLog-doc dtk-doc)

## ###################################################################
## dtkCore
## ###################################################################

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dtkCore/dtkcore.qdocconf.in ${CMAKE_CURRENT_BINARY_DIR}/dtkcore.qdocconf IMMEDIATE @ONLY)

add_custom_target(dtkCore-doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${DTK_QDOC_EXECUTABLE} dtkcore.qdocconf
  COMMAND ${QT5_QHGN_EXECUTABLE} ${CMAKE_BINARY_DIR}/html/dtkcore/dtkcore.qhp -o ${CMAKE_BINARY_DIR}/html/dtkcore.qch
  COMMENT "-- Generating dtkCore documentation")

add_dependencies(dtkCore-doc dtkMeta dtk-doc)

## ###################################################################
## dtkDistributed
## ###################################################################

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dtkDistributed/dtkdistributed.qdocconf.in ${CMAKE_CURRENT_BINARY_DIR}/dtkdistributed.qdocconf IMMEDIATE @ONLY)

add_custom_target(dtkDistributed-doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${DTK_QDOC_EXECUTABLE} dtkdistributed.qdocconf
  COMMAND ${QT5_QHGN_EXECUTABLE} ${CMAKE_BINARY_DIR}/html/dtkdistributed/dtkdistributed.qhp -o ${CMAKE_BINARY_DIR}/html/dtkdistributed.qch
  COMMENT "-- Generating dtkDistributed documentation")

add_dependencies(dtkDistributed-doc dtkCore-doc)

## ###################################################################
## ALL
## ###################################################################

add_custom_target(doc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ${DTK_QDOC_EXECUTABLE} dtkdoc.qdocconf
  COMMAND ${QT5_QHGN_EXECUTABLE} ${CMAKE_BINARY_DIR}/html/dtkdoc/dtkdoc.qhp -o ${CMAKE_BINARY_DIR}/html/dtkdoc.qch
  COMMENT "-- Generating dtk documentation")

add_dependencies(doc dtkMeta-doc dtkLog-doc dtkCore-doc dtkDistributed-doc)

######################################################################
### CMakeLists.txt ends here
