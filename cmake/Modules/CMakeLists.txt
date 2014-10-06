SET(CMAKE_MODULE_PATH "${RSC_CMAKE_MODULE_PATH}")
MESSAGE(STATUS "Installing CMake modules to: ${CMAKE_MODULE_PATH}")

INSTALL(FILES ExtractTBBVersion.cpp.in
              ExtractSpreadVersion.cpp.in
              TestAttributeConstructor.cpp
              TestCRTInit.cpp
              CheckInitMethod.cmake
              CheckLSBTypes.cmake
              CMakeDoxyfile.in
              CMakeVariableDump.cmake
              CurrentDate.cmake
              current_date.bat
              DefineProjectVersion.cmake
              EnableCoverageReport.cmake
              EnableSlocCount.cmake
              FindBoostThreadpool.cmake
              FindBoostUUID.cmake
              FindCppcheck.cmake
              FindEigen2.cmake
              FindEigen3.cmake
              FindFRI.cmake
              Findgcovr.cmake
              FindJsonCpp.cmake
              FindLcov.cmake
              FindLog4cxx.cmake
              FindMongo.cmake
              FindOpenKC.cmake
              FindProtocolBuffers.cmake
              FindQGLViewer.cmake
              FindSCC.cmake
              Findsloccount.cmake
              FindSpread.cmake
              FindTBB.cmake
              FindXenomai.cmake
              GenerateCppcheck.cmake
              GenerateDoxygen.cmake
              GitProjectVersion.cmake
              git2staticversion.py
              IgnoreReturnCode.cmake
              InstallDebugSymbols.cmake
              InstallFilesRecursive.cmake
              PadString.cmake
              ParseArguments.cmake
              PedanticCompilerWarnings.cmake
              ProvideGoogleMock.cmake
              ProvideFlexibleCPack.cmake
              SubversionIsWc.cmake
              SuperPedanticCompilerWarnings.cmake
        DESTINATION ${CMAKE_MODULE_PATH})
