# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 3.15)


set(CMAKE_SUPPRESS_REGENERATION true)

set(CMAKE_CXX_STANDARD 			17)
set(CMAKE_CXX_EXTENSIONS 		OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ROOT 				${CMAKE_SOURCE_DIR})
set(WATTYVERSION 		0.28)
set(CORE 				Watty-Core)
set(LIBNAME 			Watty_v${WATTYVERSION})
set(WATTYDIR 			${ROOT}/../)
set(COREDIR 			${WATTYDIR}${CORE}/)


set(CMAKE_CONFIGURATION_TYPES 		Debug Release Web)


add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")
add_compile_definitions(RESDIR="${CMAKE_SOURCE_DIR}/res/")


include_directories(
	${COREDIR}
	${COREDIR}include/
	${COREDIR}include/Watty
	${WATTYDIR}dependencies/stb
	${WATTYDIR}dependencies/glad/include
	${WATTYDIR}dependencies/glfw/include
	${WATTYDIR}dependencies/glad/include
	${WATTYDIR}dependencies/box2d/include
	${WATTYDIR}dependencies/soloud/include
	${WATTYDIR}dependencies/json/include
	${WATTYDIR}dependencies/glm/include
	${WATTYDIR}dependencies/imgui
	
	) 
if(EMSCRIPTEN)

	set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}  -s ENVIRONMENT=web -s LLD_REPORT_UNDEFINED -s USE_GLFW=3 -s USE_WEBGL2=1 -s FULL_ES3=1 -s WASM=0 -std=c++17 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 --memory-init-file 0")
	set(CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} ${CMAKE_SOURCE_DIR}/dependencies/box2d.js/box2d.o")
	
	set(CMAKE_BUILD_TYPE Web)
	include_directories(${CMAKE_SOURCE_DIR}/dependencies/emscripten/system/include)
	add_compile_definitions(WATTY_EMSCRIPTEN)
ENDIF()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 	${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
link_directories(${COREDIR}../bin/${CMAKE_BUILD_TYPE}/)
link_libraries(${LIBNAME})

project (Demos)

add_compile_definitions(WATTY_OPENGL)

if(EMSCRIPTEN)
	message(STATUS ${CMAKE_SOURCE_DIR})
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -o Demos.html -s USE_GLFW=3 --embed-file ${CMAKE_SOURCE_DIR}/res --embed-file ${COREDIR}/res -s TOTAL_MEMORY=27MB")
ENDIF()
add_subdirectory(SimpleGame)
add_subdirectory(PlatformerDemo)
add_subdirectory(PhysicsDemo)
add_subdirectory(TileMapDemo)
add_subdirectory(ConwaysGameOfLife)

# set_property(TARGET SimpleGame PlatformerDemo PhysicsDemo TileMapDemo ConwaysGameOfLife PROPERTY
#   MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")


