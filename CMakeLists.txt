cmake_minimum_required(VERSION 3.5)

project(DDash LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Svg REQUIRED)

add_executable(DDash
  main.cpp
  ddash.h
  ddash.cpp
  runtime.h
  runtime.cpp
  mainwindow.h
  mainwindow.cpp
  action.h
  action.cpp
  actionfile.h
  actionfile.cpp
  actionfilesize.h
  actionfilesize.cpp
  labeltext.h
  labeltext.cpp
  svgicon.h
  svgrender.h
  svgrender.cpp
  actionfileexists.h
  actionfileexists.cpp
  labelstatus.h
  labelstatus.cpp
  label.h
  label.cpp
  button.h
  button.cpp
  configuration.h
  configuration.cpp
  actionfiledate.h
  actionfiledate.cpp
  adddialog.h
  adddialog.cpp
)

target_link_libraries(DDash Qt5::Core Qt5::Widgets Qt5::Svg)
