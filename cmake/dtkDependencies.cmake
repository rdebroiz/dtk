### dtkDependencies.cmake --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Fri Apr  2 09:11:53 2010 (+0200)
## Version: $Id$
## Last-Updated: Wed Apr  4 14:41:19 2012 (+0200)
##           By: tkloczko
##     Update #: 81
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

if(NOT DTK_DEPENDDENCIES_INCLUDED)

set(NOT DTK_DEPENDDENCIES_INCLUDED ON)

## #################################################################
## Qt
## #################################################################

set(QT_USE_QTOPENGL      TRUE)
set(QT_USE_QTXML         TRUE)
set(QT_USE_QTSQL         TRUE)
set(QT_USE_QTHELP        TRUE)
set(QT_USE_QTNETWORK     TRUE)
set(QT_USE_QTWEBKIT      TRUE)

if(WIN32)
  set(QT_USE_QTMAIN TRUE)
endif(WIN32)

if(NOT QT_FOUND)
  find_package(Qt4 4.6.0 REQUIRED)
endif(NOT QT_FOUND)

if(${QT_VERSION_MAJOR} EQUAL 4 AND ${QT_VERSION_MINOR} GREATER 6)
  set(QT_USE_QTDECLARATIVE TRUE)
endif(${QT_VERSION_MAJOR} EQUAL 4 AND ${QT_VERSION_MINOR} GREATER 6)

include(${QT_USE_FILE})

mark_as_advanced(QT_QMAKE_EXECUTABLE)
mark_as_advanced(QT_QTMOTIF_INCLUDE_DIR)
mark_as_advanced(QT_QTMOTIF_LIBRARY_DEBUG)
mark_as_advanced(QT_QTMOTIF_LIBRARY_RELEASE)

## #################################################################
## Wrapping
## #################################################################

if(DTK_BUILD_WRAPPERS)

## #################################################################
## Swig
## #################################################################

mark_as_advanced(SWIG_DIR)
mark_as_advanced(SWIG_EXECUTABLE)
mark_as_advanced(SWIG_VERSION)

find_package(SWIG QUIET)

if(SWIG_FOUND)
  include(${SWIG_USE_FILE})
  set(CMAKE_SWIG_FLAGS "")
  
  macro(dtk_wrap project target name language input deps)
    
    set(wrap_output ${project}_wrap_${language}.cpp)
    
    add_custom_command(
      OUTPUT ${wrap_output}
      COMMAND ${SWIG_EXECUTABLE}
      ARGS
      "-${language}"
      "-c++"
      "-module" ${name}
      "-I${PROJECT_SOURCE_DIR}/.."
      "-outdir" ${CMAKE_CURRENT_BINARY_DIR}
      "-o" ${wrap_output}
      ${input}
      MAIN_DEPENDENCY ${input}
      COMMENT "Wrapping ${input} to ${language}")
    
    set(${target} ${${target}} ${wrap_output})
    
  endmacro(dtk_wrap)
endif(SWIG_FOUND)

if(SWIG_FOUND)
  add_definitions(-DHAVE_SWIG)
endif(SWIG_FOUND)

## #################################################################
## Tcl
## #################################################################

find_package(TCL QUIET)

if(TCL_FOUND)
  include_directories(${TCL_INCLUDE_PATH})
endif(TCL_FOUND)

if(TCL_FOUND)
  add_definitions(-DHAVE_TCL)
endif(TCL_FOUND)

## #################################################################
## Python
## #################################################################

find_package(PythonLibs QUIET)

if(PYTHONLIBS_FOUND)
  include_directories(${PYTHON_INCLUDE_DIRS})
  get_filename_component(PYTHON_PATH ${PYTHON_LIBRARIES} PATH)
  link_directories(${PYTHON_PATH})
endif(PYTHONLIBS_FOUND)

if(PYTHONLIBS_FOUND)
  add_definitions(-DHAVE_PYTHON)
endif(PYTHONLIBS_FOUND)

## #################################################################
## Editline
## #################################################################

mark_as_advanced(EDITLINE_INCLUDE_DIR)
mark_as_advanced(EDITLINE_LIBRARY)

find_path(EDITLINE_INCLUDE_DIR histedit.h
  /usr/include
  /usr/local/include)

find_library(EDITLINE_LIBRARY edit
  /usr/lib
  /usr/local/lib)

if(EDITLINE_LIBRARY)
  set(EDITLINE_FOUND "YES")
  set(DTK_HAVE_EDIT "YES")
endif(EDITLINE_LIBRARY)

## #################################################################
## Build wrappers (end)
## #################################################################

endif(DTK_BUILD_WRAPPERS)

## #################################################################
## Zlib
## #################################################################

find_package(ZLIB QUIET)

if(ZLIB_FOUND)
include_directories(${ZLIB_INCLUDE_DIRS})
endif(ZLIB_FOUND)

## #################################################################
## Ssl
## #################################################################

find_package(OpenSSL QUIET)

if(OPENSSL_FOUND)
include_directories(${OPENSSL_INCLUDE_DIR})
endif(OPENSSL_FOUND)

## #################################################################
## Mpi
## #################################################################

mark_as_advanced(MPI_EXTRA_LIBRARY)
mark_as_advanced(MPI_LIBRARY)

find_package(MPI QUIET)

if(MPI_FOUND)
include_directories(${MPI_INCLUDE_PATH})
set(COMPILE_FLAGS ${COMPILE_FLAGS} ${MPI_COMPILE_FLAGS})
set(DTK_HAVE_MPI "YES")
endif(MPI_FOUND)

## #################################################################
## Vrpn
## #################################################################

find_path(QUAT_INCLUDES           quat.h /usr/include /usr/local/include)
find_path(VRPN_INCLUDES vrpn_Configure.h /usr/include /usr/local/include)

if(QUAT_INCLUDES AND VRPN_INCLUDES)
include_directories(${QUAT_INCLUDES})
include_directories(${VRPN_INCLUDES})
endif(QUAT_INCLUDES AND VRPN_INCLUDES)

mark_as_advanced(VRPN_INCLUDES)
mark_as_advanced(QUAT_INCLUDES)

find_library(QUAT_LIBRARY NAMES quat PATHS /usr/lib /usr/local/lib)
find_library(VRPN_LIBRARY NAMES vrpn PATHS /usr/lib /usr/local/lib)

if(QUAT_LIBRARY AND VRPN_LIBRARY)
  add_definitions(-DHAVE_VRPN)
endif(QUAT_LIBRARY AND VRPN_LIBRARY)

mark_as_advanced(QUAT_LIBRARY)
mark_as_advanced(VRPN_LIBRARY)

## #################################################################
## 
## #################################################################

if(MPI_FOUND AND QUAT_LIBRARY AND VRPN_LIBRARY)
  add_definitions(-DDTK_WRAP_VRPN)

endif(MPI_FOUND AND QUAT_LIBRARY AND VRPN_LIBRARY)

## #################################################################
## Qwt
## #################################################################

find_package(Qwt QUIET)

if(QWT_FOUND)
  add_definitions(-DHAVE_PLOT)
  set(DTK_HAVE_PLOT "YES")
  include_directories(${QWT_INCLUDE_DIR})
endif(QWT_FOUND)

## #################################################################
## 
## #################################################################

mark_as_advanced(file_cmd)

endif(NOT DTK_DEPENDDENCIES_INCLUDED)

