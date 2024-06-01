cmake_minimum_required(VERSION 3.5)

project(3DViewer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OpenGL_GL_PREFERENCE "GLVND")
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS OpenGL)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS OpenGLWidgets)

set(VIEWER_LIB ${CMAKE_CURRENT_SOURCE_DIR}/../viewer.a)

set(PROJECT_SOURCES
  ./main.cpp
  ./mainwindow.cpp
  ./mainwindow.ui
  ./mainwindow.h
  ./glwidget.cpp
  ./glwidget.h
  ./../modules/parse.c
  ./../modules/matrix.c
  ./../modules/afine.c
)

set(CMAKE_AUTOUIC_SEARCH_PATHS
  ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(3DViewer ${PROJECT_SOURCES})

target_link_libraries(3DViewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(3DViewer PRIVATE Qt${QT_VERSION_MAJOR}::OpenGL)
target_link_libraries(3DViewer PRIVATE Qt${QT_VERSION_MAJOR}::OpenGLWidgets)
target_link_libraries(3DViewer PRIVATE ${VIEWER_LIB})

target_include_directories(3DViewer PRIVATE
    /home/kossadda/develop/3DViewer_v1.0/src/gui/
)

set_target_properties(3DViewer PROPERTIES
  MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
  MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
  MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
  MACOSX_BUNDLE TRUE
  WIN32_EXECUTABLE TRUE
)

install(TARGETS 3DViewer
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
  qt_finalize_executable(3DViewer)
endif()
