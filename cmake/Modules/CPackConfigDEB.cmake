set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_NAME "calc")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "i386")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Toni Cebrián")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Sample package illustrating the creating of deb packages using CMake")
set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")

# Scripts for pre or post installation
#set( CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_CURRENT_SOURCE_DIR}/CMake/debian/postinst;${CMAKE_CURRENT_SOURCE_DIR}/CMake/debian/prerm;" )
