# - Try to find QGLViewer
# Once done this will define
#
#  QGLVIEWER_FOUND - system has QGLViewer
#  QGLVIEWER_INCLUDE_DIR - the QGLViewer include directory
#  QGLVIEWER_LIBRARIES - Link these to use QGLViewer
#  QGLVIEWER_DEFINITIONS - Compiler switches required for using QGLViewer
#

message(STATUS "QGLVIEWERROOT is: \"${QGLVIEWERROOT}:$ENV{QGLVIEWERROOT}\"")

find_path(QGLVIEWER_INCLUDE_DIR 
          NAMES QGLViewer/qglviewer.h
          PATHS ${QGLVIEWERROOT}
                $ENV{QGLVIEWERROOT}
                /usr/include
                /usr/local/include
         )

if(QGLVIEWER_INCLUDE_DIR)
	message(STATUS "Found QglViewer include-dir: ${QGLVIEWER_INCLUDE_DIR}")
else()
	message(STATUS "Could NOT find QglViewer include-dir.")
endif()


find_library(QGLVIEWER_LIBRARY_RELEASE 
             NAMES qglviewer-qt4 qglviewer QGLViewer QGLViewer2
             PATHS 
                   ${QGLVIEWERROOT}
                   $ENV{QGLVIEWERROOT}
                   ENV LD_LIBRARY_PATH
                   ENV LIBRARY_PATH
		   /usr/lib
                   /usr/local/lib
             PATH_SUFFIXES QGLViewer QGLViewer/release
            )

if(QGLVIEWER_LIBRARY_RELEASE)
	message(STATUS "Found QglViewer library (release): ${QGLVIEWER_LIBRARY_RELEASE}")
else()
	message(STATUS "Could NOT find QglViewer library (release).")
endif()

find_library(QGLVIEWER_LIBRARY_DEBUG
             NAMES dqglviewer dQGLViewer dQGLViewer2
             PATHS ${QGLVIEWERROOT}
                   $ENV{QGLVIEWERROOT}
                   ENV LD_LIBRARY_PATH
                   ENV LIBRARY_PATH
		   /usr/lib
                   /usr/local/lib
             PATH_SUFFIXES QGLViewer QGLViewer/debug      
            )

if(QGLVIEWER_LIBRARY_DEBUG)
	message(STATUS "Found QglViewer library (debug): ${QGLVIEWER_LIBRARY_DEBUG}")
else()
	message(STATUS "Could NOT find QglViewer library (debug).")
endif()

if(QGLVIEWER_LIBRARY_RELEASE)
  if(QGLVIEWER_LIBRARY_DEBUG)
    set(QGLVIEWER_LIBRARIES_ optimized ${QGLVIEWER_LIBRARY_RELEASE} debug ${QGLVIEWER_LIBRARY_DEBUG})
  else()
    set(QGLVIEWER_LIBRARIES_ ${QGLVIEWER_LIBRARY_RELEASE})
  endif()

  set(QGLVIEWER_LIBRARIES ${QGLVIEWER_LIBRARIES_} CACHE FILEPATH "The QGLViewer library")

endif()

IF(QGLVIEWER_INCLUDE_DIR AND QGLVIEWER_LIBRARIES)
   SET(QGLVIEWER_FOUND TRUE)
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DQGLVIEWER_FOUND")
ENDIF(QGLVIEWER_INCLUDE_DIR AND QGLVIEWER_LIBRARIES)

IF(QGLVIEWER_FOUND)
  IF(NOT QGLViewer_FIND_QUIETLY)
    MESSAGE(STATUS "Found QGLViewer: ${QGLVIEWER_LIBRARIES}")
  ENDIF(NOT QGLViewer_FIND_QUIETLY)
ELSE(QGLVIEWER_FOUND)
  IF(QGLViewer_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Could not find QGLViewer")
  ENDIF(QGLViewer_FIND_REQUIRED)
ENDIF(QGLVIEWER_FOUND)

