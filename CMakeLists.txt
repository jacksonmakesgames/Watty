# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 3.15)

set(CMAKE_SUPPRESS_REGENERATION true)
set(CMAKE_CXX_STANDARD 			17)
set(CMAKE_CXX_EXTENSIONS 		OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CONFIGURATION_TYPES 	Debug Release)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set (USE_MSVC_RUNTIME_LIBRARY_DLL OFF)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)


# Remove 'lib' prefix for shared libraries on Windows
if (WIN32)
  set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif ()

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(SEND_ERROR "In-source builds are not allowed.")
endif ()

set(ROOT 						${CMAKE_SOURCE_DIR})
set(WATTYVERSION 				0.27)
set(CORE 						Watty-Core)
set(LIBNAME 					Watty_v${WATTYVERSION})
set(COREDIR 					${CMAKE_SOURCE_DIR}/${CORE}/)

include_directories(
	${COREDIR}ext/sdl/include
	${COREDIR}
	${COREDIR}include
	${COREDIR}include/Watty
	${COREDIR}include/ext
	${COREDIR}ext/imgui/include
	${COREDIR}ext/glm/include
	${COREDIR}ext/soloud/include
	${COREDIR}ext/stb_image/include
	${COREDIR}ext/tiny_obj_loader/include
	
	${COREDIR}ext/glad/include
	${COREDIR}ext/freetype-gl
	)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/dependencies/lib/${CMAKE_BUILD_TYPE}")
set(CMAKE_INSTALL_LIBDIR "${CMAKE_SOURCE_DIR}/dependencies/lib/${CMAKE_BUILD_TYPE}")

include_directories(${CMAKE_SOURCE_DIR}/dependencies/glfw/include)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/stb)

add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")

add_compile_definitions(
	WATTYRESDIR="${CMAKE_SOURCE_DIR}/${CORE}/res/"
	WATTYVERSION=${WATTYVERSION}
	_LIB
	CRT_SECURE_NO_WARNINGS
	_CRT_NONSTDC_NO_DEPRECATE
	WITH_SDL2
	WATTY_OPENGL
	)

##DEPS:
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/SDL)

add_subdirectory(Watty-Core)

##LIB
project (Watty_Engine)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY	 	${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY		${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

source_group("Headers"            	FILES ${HEADERS})

source_group("Watty"            	FILES ${SRC_AUDIO})
source_group("Audio"            	FILES ${SRC_AUDIO})
source_group("GameObjects"          FILES ${SRC_GAMEOBJECTS})
source_group("Graphics"            	FILES ${SRC_GRAPHICS})
source_group("Input"            	FILES ${SRC_INPUTS})
source_group("Physics"            	FILES ${SRC_PHYSICS})
source_group("Shaders"            	FILES ${SRC_SHADERS})
source_group("Utils"            	FILES ${SRC_UTILS})
# TODO: MOVE THESE TO ANOTHER FOLDER/PROJECT
source_group("ext/SoLoud"           	FILES ${SRC_SOLOUD})
source_group("ext/Freetype-gl"          FILES ${SRC_FREETYPEGL})
source_group("ext/GLAD"         		FILES ${SRC_GLAD})
source_group("ext/Box2D"         		FILES ${SRC_BOX2D}
})


## Compile:
add_library(${LIBNAME} STATIC
	$<TARGET_OBJECTS:glfw>
	$<TARGET_OBJECTS:SDL2main>
	$<TARGET_OBJECTS:Core_v${WATTYVERSION}>
	)

set_target_properties( ${LIBNAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}
)

add_subdirectory(Sandbox)