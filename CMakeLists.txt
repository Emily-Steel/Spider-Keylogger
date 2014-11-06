cmake_minimum_required(VERSION 2.8.8)

project(Project)

set(NAME_DLL "keylogger")
set(NAME_LIB "common")
set(NAME_CLIENT "client")
set(NAME_SERVER "server")
set(TEST_EXEC "UnitTester")

set(INCLUDE_DIRECTORY "${PROJECT_SOURCE_DIR}/${NAME_LIB}/inc/"
					  "${PROJECT_SOURCE_DIR}/${NAME_DLL}/inc/"
					  "${PROJECT_SOURCE_DIR}/${NAME_CLIENT}/inc/"
					  "${PROJECT_SOURCE_DIR}/${NAME_SERVER}/inc/")
set(SRC_DIRECTORY "${PROJECT_SOURCE_DIR}/${NAME_LIB}/src/"
				  "${PROJECT_SOURCE_DIR}/${NAME_DLL}/src/"
				  "${PROJECT_SOURCE_DIR}/${NAME_CLIENT}/src/"
				  "${PROJECT_SOURCE_DIR}/${NAME_SERVER}/src/")
set(DOC_PATH "${PROJECT_SOURCE_DIR}/doc")
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

set (Boost_USE_STATIC_LIBS ON)
set (Boost_MULTITHREADED ON)
set (Boost_USE_STATIC_RUNTIME OFF)

# cmake modules
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)
find_package(Threads)
find_package(Boost 1.55.0 COMPONENTS filesystem system program_options REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Sqlite3 REQUIRED)

INCLUDE(CMakeDependentOption)
INCLUDE(CheckIncludeFile)
INCLUDE(CheckIncludeFileCXX)
INCLUDE(InstallFilesRecursive)
INCLUDE(EnableCoverageReport)
INCLUDE(EnableSlocCount)
INCLUDE(GenerateDoxygen)
INCLUDE(GenerateCppcheck)
INCLUDE(GenerateCccc)
INCLUDE(GenerateValgrind)
INCLUDE(DefineProjectVersion)
INCLUDE(CurrentDate)
INCLUDE(DemangleCppABI)
INCLUDE(CheckApplyCXXCompilerFlags)
INCLUDE(GenerateExportHeader)

# --- global compiler flags ---
if (UNIX)
  COMPILER_CXX_FLAGS(FLAGS "-pipe" "-Wall" "-Wextra"
			   "--std=c++11"
			   "-Wchar-subscripts" "-Winit-self" "-Wswitch-enum"
			   "-Wstrict-aliasing=3"
			   "-Wundef" "-Wno-endif-labels"
			   "-Wshadow" "-Wno-builtin-macro-redefined"
			   "-Wmissing-declarations"
			   "-Wdocumentation"
			   "-Wno-switch-enum"
			   )
elseif (MSVC)
  COMPILER_CXX_FLAGS(FLAGS "/wd4251" # needs to have dll-interface to be used by clients
			   "/wd4275" # exported class derived from non-exported class
			   )
endif()

# --- user options ---
OPTION(BUILD_TESTS "Decide if the test suite shall be built or not." OFF)
CMAKE_DEPENDENT_OPTION(BUILD_TESTS_COVERAGE "Decide if a coverage report should be generated." ON "BUILD_TESTS" OFF)
CMAKE_DEPENDENT_OPTION(VALGRIND_CHECK "Decide if valgrind should be executed with the test binary to check for memory leaks." ON "BUILD_TESTS" OFF)
OPTION(CODE_METRICS "Decide if code's metrics should be generated." OFF)
OPTION(CODE_CHECK "Decide if code should be checked for common errors." OFF)
OPTION(GENERATE_DOC "Decide if documentation should be generated." OFF)
OPTION(BUILD_SERVER "Does the compilation will build the server ?." ON)
OPTION(BUILD_CLIENT "Does the compilation will build the client ?." ON)

# --- global definitions ---
DEFINE_PROJECT_VERSION(PROJECT 0 0 1 "snapshot")
CURRENT_DATE(PROJECT_BUILD_DATE)

# All source files using globs
file(
  GLOB_RECURSE
  lib_source_files
  ${NAME_LIB}/src/*
)

file(
  GLOB_RECURSE
  lib_include_files
  ${NAME_LIB}/inc/*
)

file(
  GLOB_RECURSE
  client_source_files
  ${NAME_CLIENT}/src/*
)

file(
  GLOB_RECURSE
  client_include_files
  ${NAME_CLIENT}/inc/*
)

file(
  GLOB_RECURSE
  dll_source_files
  ${NAME_DLL}/src/*
)

file(
  GLOB_RECURSE
  dll_include_files
  ${NAME_DLL}/inc/*
)

file(
  GLOB_RECURSE
  server_source_files
  ${NAME_SERVER}/src/*
)

file(
  GLOB_RECURSE
  server_include_files
  ${NAME_SERVER}/inc/*
)

# configure a header file to pass some of the CMake settings
# to the source code
#configure_file (
#  "${NAME_LIB}/inc/Config.h.in"
#  "${NAME_LIB}/inc/Config.h"
#)

include_directories("${INCLUDE_DIRECTORY}")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/${NAME_LIB}/inc/")

add_library(
# executable name
  ${NAME_LIB} STATIC
# source files
  ${lib_source_files}
  ${lib_include_files}
)

if(BUILD_CLIENT)
  add_library(
  # executable name
    ${NAME_DLL} SHARED
  # source files
    ${dll_source_files}
    ${dll_include_files}
  )

  GENERATE_EXPORT_HEADER( ${NAME_DLL}
               BASE_NAME ${NAME_DLL}
               EXPORT_MACRO_NAME ${NAME_DLL}_EXPORT
               EXPORT_FILE_NAME 
               STATIC_DEFINE ${NAME_DLL}_BUILT_AS_STATIC
  )

    add_executable(
  # executable name
    ${NAME_CLIENT}
 # source files
    ${client_source_files}
    ${client_include_files}
  )
  
  target_link_libraries(${NAME_DLL} ${NAME_LIB})
  target_link_libraries(${NAME_CLIENT} ${NAME_LIB})
endif()

if (BUILD_SERVER)
  add_executable(
    ${NAME_SERVER}
  # source files
    ${server_source_files}
    ${server_include_files}
  )
  
  target_link_libraries(${NAME_SERVER} ${NAME_LIB})
endif()

file(
  GLOB_RECURSE
  test_files
  test/*
)

if (THREADS_FOUND)
  target_link_libraries (${NAME_LIB} ${CMAKE_THREAD_LIBS_INIT})
endif()

if (SQLITE3_FOUND)
  include_directories(${SQLITE3_INCLUDE_DIR})
  target_link_libraries (${NAME_LIB} ${SQLITE3_LIBRARIES})
endif()

if (Boost_FOUND)
   include_directories(${Boost_INCLUDE_DIRS})
   target_link_libraries (${NAME_LIB} ${Boost_LIBRARIES})
endif()

# --- enable unit tests if desired ---
if(BUILD_TESTS)
  if(NOT CPPUNIT_FOUND)
    MESSAGE(WARNING "CppUnit library can't be found, Unit test won't be compiled")
  else()
    add_executable(
    # executable name
      ${TEST_EXEC}
    # source files
     ${test_files}
    )

    if(BUILD_TESTS_COVERAGE)
      # --- coverage report ---
      ENABLE_COVERAGE_REPORT(TARGETS ${TEST_EXEC} TESTS ${test_files})
    endif()

    if(VALGRIND_CHECK)
      # --- Valgrind --- #
      GENERATE_VALGRIND(BIN "${CMAKE_CURRENT_BINARY_DIR}/${TEST_EXEC}")
    endif()

    set(TEST_REPORT_FILE "cpptestresults.xml")
    # Execute ${CMAKE_CURRENT_BINARY_DIR}/${TEST_EXEC} binary to execute tests
    ADD_CUSTOM_COMMAND(OUTPUT ${TEST_REPORT_FILE}
                           DEPENDS ${TEST_EXEC}
                           COMMAND "${CMAKE_CURRENT_BINARY_DIR}/${TEST_EXEC}" ARGS "--xml-file=${TEST_REPORT_FILE}"
                           WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
    ADD_CUSTOM_TARGET(launchtest DEPENDS ${TEST_REPORT_FILE})

    include_directories(${CPPUNIT_INCLUDE_DIRS})
    target_link_libraries (${TEST_EXEC} ${CPPUNIT_LIBRARY} ${NAME_LIB})

  endif()
endif()

#Extra targets:
if(CODE_CHECK)
  # --- cppcheck ---
  GENERATE_CPPCHECK(SOURCES ${SRC_DIRECTORY}
                            "${PROJECT_SOURCE_DIR}/test"
                            ENABLE_IDS style
                            INLINE_SUPPRESSION)
endif()

if(CODE_METRICS)
  # --- cccc ---
  GENERATE_CCCC(SOURCES ${SRC_DIRECTORY} ${INCLUDE_DIRECTORY}
                        "${PROJECT_SOURCE_DIR}/test")
  # --- SlocCount --- #
  ENABLE_SLOCCOUNT(FOLDERS ${SRC_DIRECTORY} ${INCLUDE_DIRECTORY}
                        "${PROJECT_SOURCE_DIR}/test")
endif()

if(GENERATE_DOC)
  # --- Doxygen --- #
  GENERATE_DOXYGEN(SOURCES ${SRC_DIRECTORY} ${INCLUDE_DIRECTORY}
                        "${PROJECT_SOURCE_DIR}/test" ${DOC_PATH}
                        VERSION "${PROJECTVERSION}")
endif()
