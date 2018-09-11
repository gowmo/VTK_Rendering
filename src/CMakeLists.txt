cmake_minimum_required(VERSION 2.8)
 
SET(VTK_DIR "D:/VTK/VTK-7.1.0/VTK-bin" CACHE PATH "VTK directory override" FORCE)
 

PROJECT(FootMapper)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(FootMapper MACOSX_BUNDLE FootMapper)
 
if(VTK_LIBRARIES)
  target_link_libraries(FootMapper ${VTK_LIBRARIES})
else()
  target_link_libraries(FootMapper vtkHybrid vtkWidgets)
endif()