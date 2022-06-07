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

# Python
set(ORIG_TYPE ${CMAKE_BUILD_TYPE})
set(CMAKE_BUILD_TYPE Release)
link_directories(
	${CMAKE_BINARY_DIR}/dependencies/python-cmake/static-libs/Debug
	${CMAKE_BINARY_DIR}/dependencies/python-cmake/static-libs/Release
	${CMAKE_BINARY_DIR}/dependencies/python-cmake/CMakeBuild/python/Debug
)

add_subdirectory(
	${CMAKE_SOURCE_DIR}/dependencies/python-cmake
)
set(CMAKE_BUILD_TYPE ${ORIG_TYPE})
link_libraries(python39.lib python.lib)


include_directories(
	${CMAKE_BINARY_DIR}/dependencies/python-cmake/include
	${CMAKE_BINARY_DIR}/dependencies/Python-3.9.10/PC
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

include_directories(
	${COREDIR}/
	${COREDIR}/include/
	${COREDIR}/include/Watty
	) 

if(EXISTS "${CMAKE_BINARY_DIR}/dependencies/python-cmake/static-libs/Debug/python39.lib")
	configure_file(${CMAKE_BINARY_DIR}/dependencies/python-cmake/static-libs/Debug/python39.lib ${CMAKE_BINARY_DIR}/dependencies/python-cmake/static-libs/Debug/python39_d.lib COPYONLY)
endif()

project (Editor)

add_executable(Editor ${SRC} ${SRC_DEPS})
add_compile_definitions(WATTY_OPENGL)

