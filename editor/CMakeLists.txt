# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
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

add_compile_definitions(GL_WITH_GLAD) # for freetype


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 	${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

link_directories(${ROOT}/bin/${CMAKE_BUILD_TYPE}/)
link_libraries(${LIBNAME})

file(GLOB_RECURSE SRC 		"${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/res")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

include_directories(
	${COREDIR}/
	${COREDIR}/include/
	${COREDIR}/include/Watty
) 


project (Editor)
add_executable(Editor ${SRC})
add_compile_definitions(WATTY_OPENGL)

