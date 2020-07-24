# Install script for directory: J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D

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
    set(CMAKE_INSTALL_CONFIG_NAME "")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Box2D" TYPE FILE FILES "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Box2D.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Box2D/Collision" TYPE FILE FILES
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Collision/b2BroadPhase.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Collision/b2Collision.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Collision/b2Distance.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Collision/b2DynamicTree.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Collision/b2TimeOfImpact.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Box2D/Collision/Shapes" TYPE FILE FILES
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Collision/Shapes/b2CircleShape.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Collision/Shapes/b2EdgeShape.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Collision/Shapes/b2ChainShape.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Collision/Shapes/b2PolygonShape.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Collision/Shapes/b2Shape.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Box2D/Common" TYPE FILE FILES
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Common/b2BlockAllocator.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Common/b2Draw.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Common/b2GrowableStack.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Common/b2Math.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Common/b2Settings.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Common/b2StackAllocator.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Common/b2Timer.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Box2D/Dynamics" TYPE FILE FILES
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Dynamics/b2Body.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Dynamics/b2ContactManager.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Dynamics/b2Fixture.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Dynamics/b2Island.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Dynamics/b2TimeStep.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Dynamics/b2World.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Dynamics/b2WorldCallbacks.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Box2D/Dynamics/Contacts" TYPE FILE FILES
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Dynamics/Contacts/b2CircleContact.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Dynamics/Contacts/b2Contact.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Dynamics/Contacts/b2ContactSolver.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Dynamics/Contacts/b2PolygonContact.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Box2D/Dynamics/Joints" TYPE FILE FILES
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Dynamics/Joints/b2DistanceJoint.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Dynamics/Joints/b2FrictionJoint.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Dynamics/Joints/b2GearJoint.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Dynamics/Joints/b2Joint.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Dynamics/Joints/b2MotorJoint.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Dynamics/Joints/b2MouseJoint.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Dynamics/Joints/b2PrismaticJoint.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Dynamics/Joints/b2PulleyJoint.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Dynamics/Joints/b2RevoluteJoint.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Dynamics/Joints/b2RopeJoint.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Dynamics/Joints/b2WeldJoint.h"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Dynamics/Joints/b2WheelJoint.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Box2D/Rope" TYPE FILE FILES "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/Rope/b2Rope.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/objects/Box2D" TYPE FILE FILES
    "Dynamics/Joints/b2DistanceJoint.cpp.o"
    "Dynamics/Joints/b2FrictionJoint.cpp.o"
    "Dynamics/Joints/b2GearJoint.cpp.o"
    "Dynamics/Joints/b2Joint.cpp.o"
    "Dynamics/Joints/b2MotorJoint.cpp.o"
    "Dynamics/Joints/b2MouseJoint.cpp.o"
    "Dynamics/Joints/b2PrismaticJoint.cpp.o"
    "Dynamics/Joints/b2PulleyJoint.cpp.o"
    "Dynamics/Joints/b2RevoluteJoint.cpp.o"
    "Dynamics/Joints/b2RopeJoint.cpp.o"
    "Dynamics/Joints/b2WeldJoint.cpp.o"
    "Dynamics/Joints/b2WheelJoint.cpp.o"
    "Dynamics/Contacts/b2CircleContact.cpp.o"
    "Dynamics/Contacts/b2Contact.cpp.o"
    "Dynamics/Contacts/b2ContactSolver.cpp.o"
    "Dynamics/Contacts/b2PolygonAndCircleContact.cpp.o"
    "Dynamics/Contacts/b2EdgeAndCircleContact.cpp.o"
    "Dynamics/Contacts/b2EdgeAndPolygonContact.cpp.o"
    "Dynamics/Contacts/b2ChainAndCircleContact.cpp.o"
    "Dynamics/Contacts/b2ChainAndPolygonContact.cpp.o"
    "Dynamics/Contacts/b2PolygonContact.cpp.o"
    "Dynamics/b2Body.cpp.o"
    "Dynamics/b2ContactManager.cpp.o"
    "Dynamics/b2Fixture.cpp.o"
    "Dynamics/b2Island.cpp.o"
    "Dynamics/b2World.cpp.o"
    "Dynamics/b2WorldCallbacks.cpp.o"
    "Common/b2BlockAllocator.cpp.o"
    "Common/b2Draw.cpp.o"
    "Common/b2Math.cpp.o"
    "Common/b2Settings.cpp.o"
    "Common/b2StackAllocator.cpp.o"
    "Common/b2Timer.cpp.o"
    "Collision/Shapes/b2CircleShape.cpp.o"
    "Collision/Shapes/b2EdgeShape.cpp.o"
    "Collision/Shapes/b2ChainShape.cpp.o"
    "Collision/Shapes/b2PolygonShape.cpp.o"
    "Collision/b2BroadPhase.cpp.o"
    "Collision/b2CollideCircle.cpp.o"
    "Collision/b2CollideEdge.cpp.o"
    "Collision/b2CollidePolygon.cpp.o"
    "Collision/b2Collision.cpp.o"
    "Collision/b2Distance.cpp.o"
    "Collision/b2DynamicTree.cpp.o"
    "Collision/b2TimeOfImpact.cpp.o"
    "Rope/b2Rope.cpp.o"
    FILES_FROM_DIR "J:/OneDrive/Projects/Game_Development/Watty/build_web/dependencies/box2d/Box2D_v2.3.1/Box2D/CMakeFiles/Box2D.dir/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/Box2D/Box2D-targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/Box2D/Box2D-targets.cmake"
         "J:/OneDrive/Projects/Game_Development/Watty/build_web/dependencies/box2d/Box2D_v2.3.1/Box2D/CMakeFiles/Export/lib/Box2D/Box2D-targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/Box2D/Box2D-targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/Box2D/Box2D-targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Box2D" TYPE FILE FILES "J:/OneDrive/Projects/Game_Development/Watty/build_web/dependencies/box2d/Box2D_v2.3.1/Box2D/CMakeFiles/Export/lib/Box2D/Box2D-targets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Box2D" TYPE FILE FILES "J:/OneDrive/Projects/Game_Development/Watty/build_web/dependencies/box2d/Box2D_v2.3.1/Box2D/CMakeFiles/Export/lib/Box2D/Box2D-targets-noconfig.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Box2D" TYPE FILE FILES
    "J:/OneDrive/Projects/Game_Development/Watty/build_web/dependencies/box2d/Box2D_v2.3.1/Box2D/Box2DConfig.cmake"
    "J:/OneDrive/Projects/Game_Development/Watty/dependencies/box2d/Box2D_v2.3.1/Box2D/UseBox2D.cmake"
    )
endif()

