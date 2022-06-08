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
# set(Python_FIND_REGISTRY LAST)
# set(CMAKE_FIND_REGISTRY LAST)
set(Python3_FIND_VIRTUALENV FIRST)
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
if(NOT ${Python3_FOUND})
message("Python3 not found, please install it")
	exit(1)

endif()

# TODO ONLY IF DEBUG
list(GET Python3_LIBRARIES -1 PY_LAST_LIB)
if(NOT EXISTS "${PY_LAST_LIB}")
string(FIND ${PY_LAST_LIB} "_d" _index)
if (NOT ${_index} GREATER 0)
	string(REPLACE ".lib" "_d.lib" PY_LIB_D ${PY_LAST_LIB})
	else()
		set(PY_LIB_D ${PY_LAST_LIB})
	endif()
	message("Adding debug version of ${PY_LIB_D}")
	configure_file("${PY_LAST_LIB}" "${PY_LIB_D}" COPYONLY)
endif()

message("Python3_INCLUDE_DIRS: ${Python3_INCLUDE_DIRS}")
message("Python3_LIBRARY_DIRS: ${Python3_LIBRARY_DIRS}")
message("Python3_LIBRARIES: ${Python3_LIBRARIES}")

include_directories(${Python3_INCLUDE_DIRS})
link_directories(${Python3_LIBRARY_DIRS})
link_libraries(${Python3_LIBRARIES})

include_directories(
	${COREDIR}/
	${COREDIR}/include/
	${COREDIR}/include/Watty
	) 
	
project (Editor)

add_executable(Editor ${SRC} ${SRC_DEPS})
add_compile_definitions(WATTY_OPENGL)

