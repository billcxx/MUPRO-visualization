cmake_minimum_required(VERSION 2.8.8)
if(POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
endif()
if(POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW) # CMake 3.0
endif()
if(POLICY CMP0043)
  cmake_policy(SET CMP0043 NEW) # CMake 3.0
endif()
if(POLICY CMP0053)
  cmake_policy(SET CMP0053 NEW) # CMake 3.1
endif()


project(SimpleView)

#set(VTK_DIR "/usr/local/lib")
#set(VTK_DIR "C:\Program/ Files\VTK\lib\cmake\vtk-8.0")

# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 

#SET(CMAKE_INSTALL_RPATH "/usr/local/vtk7-share/lib")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
# SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


# the RPATH to be used when installing, but only if it's not a system directory
LIST(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
IF("${isSystemDir}" STREQUAL "-1")
   SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
ENDIF("${isSystemDir}" STREQUAL "-1")

find_package(VTK REQUIRED)
find_package(VTK COMPONENTS   
  vtkRenderingVolumeOpenGL2
  vtkFiltersGeometry
  vtkInteractionStyle
  vtkViewsQt
  vtkIOXML
  vtkIOExport
  vtkIOXMLParser
  vtkIOLegacy
)
include(${VTK_USE_FILE})

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# Set your files and resources here
set( Srcs main.cxx SimpleView.cxx qcustomplot.cpp column1D.cpp batch3D.cpp domainCriteria.cpp VO2Criteria.cpp)

set( Hdrs SimpleView.h qcustomplot.h column1D.h batch3D.h domainCriteria.h VO2Criteria.h)

set( MOC_Hdrs SimpleView.h column1D.h batch3D.h domainCriteria.h VO2Criteria.h)

set( UIs SimpleView.ui column1D.ui batch3D.ui domainCriteria.ui VO2Criteria.ui)

set( QRCs Icons/icons.qrc )


# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)


# We have ui files, this will bring in the macro: qt5_wrap_ui
find_package(Qt5 COMPONENTS Widgets REQUIRED QUIET)
qt5_wrap_ui(UI_Srcs ${UIs})
qt5_add_resources(QRC_Srcs ${QRCs} )

source_group("Resources" FILES
  ${UIs}
  ${QRCs}
  ${EXE_ICON} # Not present
)

source_group("Generated" FILES
  ${UI_Srcs}
  ${MOC_Srcs}
  ${QRC_Srcs}
  ${QRC_Srcs}
)

MESSAGE("vtk library" ${VTK_LIBRARIES} )
MESSAGE("QT library" ${QT_LIBRARIES} )


if(WIN32)
add_executable(SimpleView WIN32
  ${Srcs} ${Hdrs} ${UI_Srcs} ${MOC_Hdrs} ${QRC_Srcs})
else()
add_executable(SimpleView MACOSX_BUNDLE
    ${Srcs} ${Hdrs} ${UI_Srcs} ${MOC_Hdrs} ${QRC_Srcs})
endif(WIN32)
qt5_use_modules(SimpleView Core Gui Widgets PrintSupport)
target_link_libraries(SimpleView 
  vtkRenderingVolumeOpenGL2
  vtkInteractionStyle
  vtkViewsQt
  vtkIOLegacy
  vtkIOXML
  vtkIOExport
  vtkIOXMLParser
  vtkFiltersGeometry
  vtkFiltersFlowPaths
  vtkFiltersSources
  ${VTK_LIBRARIES}
)

if(WIN32)

MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()


install(TARGETS SimpleView DESTINATION bin)

MESSAGE(STATUS ${CMAKE_CURRENT_BINARY_DIR})

file( GLOB pattern_files "${CMAKE_CURRENT_BINARY_DIR}/Release/*.dll")
SUBDIRLIST(subdir_list "${CMAKE_CURRENT_BINARY_DIR}/Release/")

#get_directory_property(subdir_list DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/Release/*" SUBDIRECTORIES)

install(FILES ${pattern_files} DESTINATION bin)
FOREACH(subdir ${subdir_list})
	install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/Release/${subdir}" DESTINATION bin/${subdir})
	MESSAGE(STATUS ${subdir})
ENDFOREACH()
MESSAGE(STATUS ${wxWidgets_LIBRARIES})
MESSAGE(STATUS ${pattern_files})
# build a CPack driven installer package
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE  
     "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
include (CPack)

endif(WIN32)