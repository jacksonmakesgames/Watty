# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 3.15)


set(CMAKE_SUPPRESS_REGENERATION true)

set(CMAKE_CXX_STANDARD 			17)
set(CMAKE_CXX_EXTENSIONS 		OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ROOT 				${CMAKE_SOURCE_DIR})
set(WATTYVERSION 		0.30.0)
set(CORE 				Watty-Core)
set(LIBNAME 			Watty_v${WATTYVERSION})
set(WATTYDIR 			${ROOT}/../)
set(COREDIR 			${WATTYDIR}${CORE}/)


set(CMAKE_CONFIGURATION_TYPES 		Debug Release Web)


add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")
add_compile_definitions(RESDIR="${CMAKE_SOURCE_DIR}/res/")
add_compile_definitions(WATTY_RES_DIR="${COREDIR}res/")
add_compile_definitions(FT2_BUILD_LIBRARY)


include_directories(
	${COREDIR}
	${COREDIR}include/
	${COREDIR}include/Watty
	${WATTYDIR}dependencies/stb
	${WATTYDIR}dependencies/glfw/include
	${WATTYDIR}dependencies/glad/include
	${WATTYDIR}dependencies/freetype-gl
	${WATTYDIR}dependencies/freetype/include
	${WATTYDIR}dependencies/box2d/Box2D_v2.3.1
	${WATTYDIR}dependencies/soloud/include
	${WATTYDIR}dependencies/json/include
	${WATTYDIR}dependencies/glm/include
	${WATTYDIR}dependencies/imgui
	${WATTYDIR}dependencies/imgui/examples
) 

if(EMSCRIPTEN)

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 -s WARN_UNALIGNED=1 -s ENVIRONMENT=web -s LLD_REPORT_UNDEFINED -s USE_GLFW=3 -s USE_WEBGL2=1 -s FULL_ES3=1 -s ALLOW_MEMORY_GROWTH=1 -s DISABLE_EXCEPTION_CATCHING=2 --embed-file ${CMAKE_SOURCE_DIR}/res --embed-file ${COREDIR}/res --no-heap-copy")
	set(CMAKE_BUILD_TYPE Web)
	include_directories(${CMAKE_SOURCE_DIR}/dependencies/emscripten/system/include)
	add_compile_definitions(WATTY_EMSCRIPTEN)
else()
	add_compile_definitions(GL_WITH_GLAD)
	include_directories(${WATTYDIR}dependencies/glad/include)


ENDIF()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 	${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
link_directories(${COREDIR}../bin/${CMAKE_BUILD_TYPE}/)
link_libraries(${LIBNAME})

project (Demos)

add_compile_definitions(WATTY_OPENGL)

add_subdirectory(SimpleGame)
add_subdirectory(PlatformerDemo)
add_subdirectory(PhysicsDemo)
add_subdirectory(TileMapDemo)
add_subdirectory(ConwaysGameOfLife)

# set_property(TARGET SimpleGame PlatformerDemo PhysicsDemo TileMapDemo ConwaysGameOfLife PROPERTY
#   MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")


