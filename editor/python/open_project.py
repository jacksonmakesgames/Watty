import os

__watty_version__ = "0.31.0"
__project_name__ = ""

cmake_template = """
cmake_minimum_required (VERSION 3.3)
cmake_policy(SET CMP0057 NEW)

set(CMAKE_SUPPRESS_REGENERATION true)
set(CMAKE_CXX_STANDARD 			17)
set(CMAKE_CXX_EXTENSIONS 		OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message("Watty install directory: <$ENV{WATTYDIR}>")
if(NOT DEFINED ENV{WATTYDIR})
	message(FATAL_ERROR "Please define WATTYDIR as the directory where Watty is installed")
endif()

set(WATTYDIR $ENV{WATTYDIR})

set(WATTYVERSION 				__watty_version__)
set(CORE 				Watty-Core)
set(LIBNAME 			Watty_v${WATTYVERSION})
set(COREDIR 			${WATTYDIR}/${CORE})

set(CMAKE_CONFIGURATION_TYPES 		Debug Release Web)
add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")

add_compile_definitions(FT2_BUILD_LIBRARY)
add_compile_definitions(GL_WITH_GLAD) # for freetype

set_property(
		GLOBAL
        APPEND
        PROPERTY ADDITIONAL_CLEAN_FILES "${CMAKE_CURRENT_SOURCE_DIR}/res/*_resource_cache.txt"
)

if(${REBUILD_RES})
	file(REMOVE(
			"${CMAKE_CURRENT_SOURCE_DIR}/res/RawResources_resource_cache.txt"
			"${CMAKE_CURRENT_SOURCE_DIR}/res/res.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/res/res.h"
	))
endif()

include(${WATTYDIR}/tools/functions.cmake)
create_resources("${CMAKE_CURRENT_SOURCE_DIR}/assets" OFF)
create_resources("${CMAKE_CURRENT_SOURCE_DIR}/scenes" OFF)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/assets")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/scenes")

project(Resources)
	file(GLOB_RECURSE RES_INPUTS 		"*/res.cpp")
	file(GLOB_RECURSE RES_HEADER 		"*/res.h")
	add_library(Resources OBJECT
		${RES_HEADER}
		${RES_INPUTS}
	)

include_directories(
	${COREDIR}/
	${COREDIR}/include/
	${COREDIR}/include/Watty
	${WATTYDIR}/dependencies/stb
	${WATTYDIR}/dependencies/glad/include
	${WATTYDIR}/dependencies/glfw/include
	${WATTYDIR}/dependencies/freetype/include
	${WATTYDIR}/dependencies/freetype-gl
	${WATTYDIR}/dependencies/box2d/include
	${WATTYDIR}/dependencies/soloud/include
	${WATTYDIR}/dependencies/json/include
	${WATTYDIR}/dependencies/glm/include
	${WATTYDIR}/dependencies/imgui
	${WATTYDIR}/dependencies/imgui/examples
) 

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 	${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
#link_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/)
link_directories(${WATTYDIR}/bin/${CMAKE_BUILD_TYPE})
link_libraries(${LIBNAME})
link_libraries($<TARGET_OBJECTS:Resources>)

add_compile_definitions(WATTY_OPENGL)
project (__project_name__)
include_directories(include)
file(GLOB_RECURSE SOURCES "src/**.cpp")
file(GLOB_RECURSE HEADERS "**.h")
add_executable(__project_name__ ${SOURCES} ${HEADERS} )

"""

cmake_template = cmake_template.replace("__watty_version__", __watty_version__)
cmake_template = cmake_template.replace("__project_name__", __project_name__)

if __name__ == "__main__":
    print(cmake_template)