if(EMSCRIPTEN)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --embed-file ${CMAKE_CURRENT_SOURCE_DIR}/res/@/")
	add_compile_definitions(RESDIR="${CMAKE_CURRENT_SOURCE_DIR}/res/")
endif()
project (Sandbox)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY		${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

create_resources("${CMAKE_CURRENT_SOURCE_DIR}/res" OFF)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/res")


project(Resources)
	file(GLOB_RECURSE RES_INPUTS 		"*/res.cpp")
	file(GLOB_RECURSE RES_HEADER 		"*/res.h")
	add_library(Resources OBJECT
		${RES_HEADER}
		${RES_INPUTS}
	)

add_executable(Sandbox src/Sandbox.cpp)

set_target_properties(Sandbox PROPERTIES
  MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

target_link_directories(Sandbox
	PRIVATE ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}
	)


target_link_libraries(Sandbox
	PRIVATE ${LIBNAME}
	PRIVATE Resources
	)


