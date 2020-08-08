cmake_minimum_required (VERSION 3.15)

file(GLOB_RECURSE HEADERS 		"${COREDIR}/src/**.h*" "${COREDIR}/include/**.h*")

file(GLOB_RECURSE SRC_AUDIO 		"${COREDIR}/src/audio/**.cpp")
file(GLOB_RECURSE SRC_GAMEOBJECTS 	"${COREDIR}/src/gameobjects/**.cpp")
file(GLOB_RECURSE SRC_GRAPHICS 		"${COREDIR}/src/graphics/**.cpp")
file(GLOB_RECURSE SRC_INPUTS 		"${COREDIR}/src/input/**.cpp")
file(GLOB_RECURSE SRC_PHYSICS 		"${COREDIR}/src/physics/**.cpp")
file(GLOB_RECURSE SRC_SHADERS 		"${COREDIR}/src/shaders/**.cpp")
file(GLOB_RECURSE SRC_UTILS 		"${COREDIR}/src/utils/**.cpp")
file(GLOB_RECURSE SRC_ECS 			"${COREDIR}/src/ecs/**.cpp")

file(GLOB_RECURSE SRC_SOLOUD 			"${COREDIR}/ext/soloud/src/audiosource/**.c*" "${COREDIR}/ext/soloud/src/backend/sdl/**.c*" "${COREDIR}/ext/soloud/src/filter/**.c*" "${COREDIR}/ext/soloud/src/core/**.c*")
file(GLOB_RECURSE SRC_FREETYPEGL 		"${COREDIR}/ext/freetype-gl/*.c")


create_resources("${CMAKE_CURRENT_SOURCE_DIR}/res" ON)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/res")
file(GLOB RES_SRC 		"${CMAKE_CURRENT_SOURCE_DIR}/res/res_watty.cpp")
file(GLOB RES_HEAD 		"${CMAKE_CURRENT_SOURCE_DIR}/res/res_watty.cpp")

project (${CORENAME})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
     PREFIX ""
     FILES ${HEADERS})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
     PREFIX ""
     FILES ${SRC_SOLOUD})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
     PREFIX ""
     FILES  ${SRC_AUDIO})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
     PREFIX ""
     FILES ${SRC_GAMEOBJECTS})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
     PREFIX ""
     FILES ${SRC_GRAPHICS})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
     PREFIX ""
     FILES ${SRC_INPUTS})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
     PREFIX ""
     FILES ${SRC_GRAPHICS})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
     PREFIX ""
     FILES ${SRC_PHYSICS})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
     PREFIX ""
     FILES ${SRC_SHADERS})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
     PREFIX ""
     FILES ${SRC_UTILS})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
     PREFIX ""
     FILES ${SRC_ECS})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
     PREFIX ""
	 FILES ${RES_SRC})
	 

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
     PREFIX ""
	 FILES ${RES_HEAD})
	 


add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")

if(EMSCIPTEN)
add_library(${CORENAME} STATIC
	${HEADERS}
	${SRC_SOLOUD}
	${SRC_FREETYPEGL}
	${SRC_AUDIO}
	${SRC_GAMEOBJECTS}
	${SRC_GRAPHICS}
	${SRC_INPUTS}
	${SRC_PHYSICS}
	${SRC_SHADERS}
	${SRC_UTILS}
	${SRC_ECS}
	${RES_SRC}
	)
	
else()
	
	add_library(${CORENAME} OBJECT
		${HEADERS}
		${SRC_SOLOUD}
		${SRC_FREETYPEGL}
		${SRC_AUDIO}
		${SRC_GAMEOBJECTS}
		${SRC_GRAPHICS}
		${SRC_INPUTS}
		${SRC_PHYSICS}
		${SRC_SHADERS}
		${SRC_UTILS}
		${SRC_ECS}
		${RES_SRC}
	)


endif()

if(NOT DEFINED CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()




