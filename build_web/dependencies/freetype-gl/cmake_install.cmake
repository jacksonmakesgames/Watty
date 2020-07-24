# Install script for directory: J:/OneDrive/Projects/Game_Development/Watty/dependencies/freetype-gl

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Box2D")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Web")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/freetype-gl" TYPE FILE PERMISSIONS OWNER_READ GROUP_READ WORLD_READ FILES
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/freetype-gl/distance-field.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/freetype-gl/edtaa3func.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/freetype-gl/font-manager.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/freetype-gl/freetype-gl.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/freetype-gl/markup.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/freetype-gl/platform.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/freetype-gl/text-buffer.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/freetype-gl/texture-atlas.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/freetype-gl/texture-font.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/freetype-gl/utf8-utils.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/freetype-gl/vec234.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/freetype-gl/vector.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/freetype-gl/vertex-attribute.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/freetype-gl/vertex-buffer.h"
    )
endif()

