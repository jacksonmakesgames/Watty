# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 3.15)


set(CMAKE_SUPPRESS_REGENERATION true)

set(CMAKE_CXX_STANDARD 			17)
set(CMAKE_CXX_EXTENSIONS 		OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ROOT 				${CMAKE_SOURCE_DIR})
set(WATTYVERSION 		0.27)
set(CORE 				Watty-Core)
set(LIBNAME 			Watty_v${WATTYVERSION})
set(WATTYDIR 			${ROOT}/../)
set(COREDIR 			${WATTYDIR}${CORE}/)


set(CMAKE_CONFIGURATION_TYPES 		Debug Release)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 	${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")


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
	${WATTYDIR}dependencies/imgui/include
	
	) 

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


