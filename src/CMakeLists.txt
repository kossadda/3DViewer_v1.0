cmake_minimum_required(VERSION 3.5)

project(3d_viewer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OpenGL_GL_PREFERENCE "GLVND")

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS OpenGL)
find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)

set(VIEWER_LIB ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.a)

set(PROJECT_SOURCES
  ./gui/main.cpp
  ./gui/viewer.cpp
  ./gui/viewer.ui
  ./gui/viewer.h
  ./gui/glwidget.cpp
  ./gui/glwidget.h
  ./gui/gif.h
  ./modules/parse.c
  ./modules/matrix.c
  ./modules/afine.c
  ./modules/include/parse.h
  ./modules/include/matrix.h
  ./modules/include/afine.h
  ./modules/include/common.h
  ./modules/include/objects.h
  ./resources/resource.qrc
)

set(CMAKE_AUTOUIC_SEARCH_PATHS
  ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::OpenGL)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::OpenGLWidgets)
target_link_libraries(${PROJECT_NAME} PRIVATE ${VIEWER_LIB})

target_include_directories(${PROJECT_NAME} PRIVATE
  ./gui
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
  MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
  MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
  MACOSX_BUNDLE TRUE
  WIN32_EXECUTABLE TRUE
)

install(TARGETS ${PROJECT_NAME}
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_finalize_executable(${PROJECT_NAME})
