project (Watty_Core${WATTYVERSION})

file(GLOB_RECURSE HEADERS 		"${COREDIR}/src/**.h*" "${COREDIR}/include/**.h*")

file(GLOB_RECURSE SRC_AUDIO 		"${COREDIR}/src/audio/**.cpp")
file(GLOB_RECURSE SRC_GAMEOBJECTS 	"${COREDIR}/src/gameobjects/**.cpp")
file(GLOB_RECURSE SRC_GRAPHICS 		"${COREDIR}/src/graphics/**.cpp")
file(GLOB_RECURSE SRC_INPUTS 		"${COREDIR}/src/input/**.cpp")
file(GLOB_RECURSE SRC_PHYSICS 		"${COREDIR}/src/physics/**.cpp")
file(GLOB_RECURSE SRC_SHADERS 		"${COREDIR}/src/shaders/**.cpp")
file(GLOB_RECURSE SRC_UTILS 		"${COREDIR}/src/utils/**.cpp")


file(GLOB_RECURSE SRC_SOLOUD 			"${COREDIR}/ext/soloud/src/audiosource/**.c*" "${COREDIR}/ext/soloud/src/backend/sdl/**.c*" "${COREDIR}/ext/soloud/src/filter/**.c*" "${COREDIR}/ext/soloud/src/core/**.c*")
file(GLOB_RECURSE SRC_FREETYPEGL 		"${COREDIR}/ext/freetype-gl/*.c")
file(GLOB_RECURSE SRC_GLAD 				"${COREDIR}/ext/glad/*")
file(GLOB_RECURSE SRC_BOX2D 			"${COREDIR}/ext/Box2D/*")



add_library(Core_v${WATTYVERSION} OBJECT
	${EXT_FILES}
	${HEADERS}
	${SRC_SOLOUD}
	${SRC_FREETYPEGL}
	${SRC_GLAD}
	${SRC_BOX2D}

	${SRC_AUDIO}
	${SRC_GAMEOBJECTS}
	${SRC_GRAPHICS}
	${SRC_INPUTS}
	${SRC_PHYSICS}
	${SRC_SHADERS}
	${SRC_UTILS}
	)


set_target_properties(Core_v${WATTYVERSION}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}
)
# ## Link
target_link_directories(Core_v${WATTYVERSION}
	PUBLIC ${COREDIR}ext/FreeImage/lib/${CMAKE_BUILD_TYPE}	
	)

target_link_libraries(Core_v${WATTYVERSION}
	PUBLIC opengl32
	)

set_property(TARGET Core_v${WATTYVERSION} PROPERTY
  MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")




