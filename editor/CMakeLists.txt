cmake_minimum_required (VERSION 3.15)
set(CMAKE_SUPPRESS_REGENERATION true)

set(CMAKE_CXX_STANDARD 			17)
set(CMAKE_CXX_EXTENSIONS 		OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ROOT 				"${CMAKE_SOURCE_DIR}/..")
set(WATTYVERSION 		0.31.0)
set(CORE 				Watty-Core)
set(LIBNAME 			Watty_v${WATTYVERSION})
set(WATTYDIR 			${ROOT})
set(COREDIR 			${WATTYDIR}/${CORE})

set(CMAKE_CONFIGURATION_TYPES 		Debug Release)

add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 	${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

# Dependencies
include_directories(
	${WATTYDIR}/dependencies/imgui
	${WATTYDIR}/dependencies/imgui/examples
	${WATTYDIR}/dependencies/glm/include
	${WATTYDIR}/dependencies/tiny_obj_loader/include
	${WATTYDIR}/dependencies/glfw/include
	${WATTYDIR}/dependencies/stb
	${WATTYDIR}/dependencies/freetype-gl
	${WATTYDIR}/dependencies/freetype/include
	${WATTYDIR}/dependencies/soloud/include
	${WATTYDIR}/dependencies/json/include
	${WATTYDIR}/dependencies/emscripten/system/include
	${WATTYDIR}/dependencies/box2d/include
	${WATTYDIR}/dependencies/glad/include
	)
	
	include_directories(
		${CMAKE_SOURCE_DIR}/dependencies/tinyfiledialogs/include
		)
		
		add_compile_definitions(GL_WITH_GLAD) # for freetype # TODO check if needed
		
		link_directories(${ROOT}/bin/${CMAKE_BUILD_TYPE}/)
		link_libraries(${LIBNAME})
		
		file(GLOB_RECURSE SRC 		"${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp")
		file(GLOB_RECURSE SRC_DEPS 		"${CMAKE_CURRENT_SOURCE_DIR}/dependencies/**.cpp")
		
		message("SRC: ${SRC}")
		message("SRC_DEPS: ${SRC_DEPS}")
		
		include_directories("${CMAKE_CURRENT_SOURCE_DIR}/res")
		include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
		
# Python
set(Python3_FIND_VIRTUALENV FIRST)
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
if(NOT ${Python3_FOUND})
	message("Python3 not found, please install it")
	exit(1)
endif()

message("Python3_INCLUDE_DIRS: ${Python3_INCLUDE_DIRS}")
message("Python3_LIBRARY_DIRS: ${Python3_LIBRARY_DIRS}")
message("Python3_LIBRARIES: ${Python3_LIBRARIES}")

include_directories(${Python3_INCLUDE_DIRS})
link_directories(${Python3_LIBRARY_DIRS})
link_libraries(${Python3_LIBRARIES})

add_compile_definitions(WATTYDIR ${WATTYDIR})

# resources 
include(${WATTYDIR}/tools/functions.cmake)
create_resources("${CMAKE_CURRENT_SOURCE_DIR}/python" OFF)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
project(Resources)
	file(GLOB_RECURSE RES_INPUTS 		"*/res.cpp")
	file(GLOB_RECURSE RES_HEADER 		"*/res.h")
	add_library(Resources OBJECT
		${RES_HEADER}
		${RES_INPUTS}
	)

link_libraries($<TARGET_OBJECTS:Resources>)


include_directories(
	${COREDIR}/
	${COREDIR}/include/
	${COREDIR}/include/Watty
	) 


project (Editor)
add_executable(Editor ${SRC} ${SRC_DEPS})
add_compile_definitions(WATTY_OPENGL)



# copy watty dependencies to editor for building projects later
# TODO: come on
if (${COPY_WATTY_DEPENDENCIES})
add_custom_command(
        TARGET Editor 
        COMMAND ${CMAKE_COMMAND} -E copy_directory
		${ROOT}/bin/
		${CMAKE_SOURCE_DIR}/bin/watty/bin/)
		
add_custom_command(
		TARGET Editor
		COMMAND ${CMAKE_COMMAND} -E copy_directory
			${WATTYDIR}/dependencies/imgui
			${CMAKE_SOURCE_DIR}/bin/watty/dependencies/imgui)

add_custom_command(
		TARGET Editor
		COMMAND ${CMAKE_COMMAND} -E copy_directory
			${WATTYDIR}/dependencies/glm/include
			${CMAKE_SOURCE_DIR}/bin/watty/dependencies/glm/include)


add_custom_command(
		TARGET Editor
		COMMAND ${CMAKE_COMMAND} -E copy_directory
			${WATTYDIR}/dependencies/tiny_obj_loader/include
			${CMAKE_SOURCE_DIR}/bin/watty/dependencies/tiny_obj_loader/include)

add_custom_command(
		TARGET Editor
		COMMAND ${CMAKE_COMMAND} -E copy_directory
			${WATTYDIR}/dependencies/glfw/include
			${CMAKE_SOURCE_DIR}/bin/watty/dependencies/glfw/include)


add_custom_command(
		TARGET Editor
		COMMAND ${CMAKE_COMMAND} -E copy_directory
			${WATTYDIR}/dependencies/stb
			${CMAKE_SOURCE_DIR}/bin/watty/dependencies/stb)
		
add_custom_command(
		TARGET Editor
		COMMAND ${CMAKE_COMMAND} -E copy_directory
			${WATTYDIR}/dependencies/freetype-gl
			${CMAKE_SOURCE_DIR}/bin/watty/dependencies/freetype-gl)

add_custom_command(
		TARGET Editor
		COMMAND ${CMAKE_COMMAND} -E copy_directory
			${WATTYDIR}/dependencies/freetype/include
			${CMAKE_SOURCE_DIR}/bin/watty/dependencies/freetype/include)
				
add_custom_command(
		TARGET Editor
		COMMAND ${CMAKE_COMMAND} -E copy_directory
			${WATTYDIR}/dependencies/soloud/include
			${CMAKE_SOURCE_DIR}/bin/watty/dependencies/soloud/include)
				
add_custom_command(
		TARGET Editor
		COMMAND ${CMAKE_COMMAND} -E copy_directory
			${WATTYDIR}/dependencies/json/include
			${CMAKE_SOURCE_DIR}/bin/watty/dependencies/json/include)
				
				
add_custom_command(
		TARGET Editor
		COMMAND ${CMAKE_COMMAND} -E copy_directory
			${WATTYDIR}/dependencies/emscripten
			${CMAKE_SOURCE_DIR}/bin/watty/dependencies/emscripten)
				
add_custom_command(
		TARGET Editor
		COMMAND ${CMAKE_COMMAND} -E copy_directory
			${WATTYDIR}/dependencies/box2d/include
			${CMAKE_SOURCE_DIR}/bin/watty/dependencies/box2d/include)


add_custom_command(
		TARGET Editor
		COMMAND ${CMAKE_COMMAND} -E copy_directory
			${WATTYDIR}/dependencies/glad/include
			${CMAKE_SOURCE_DIR}/bin/watty/dependencies/glad/include)

add_custom_command(
		TARGET Editor
		COMMAND ${CMAKE_COMMAND} -E copy_directory
			${WATTYDIR}/tools/
			${CMAKE_SOURCE_DIR}/bin/watty/tools)


endif()