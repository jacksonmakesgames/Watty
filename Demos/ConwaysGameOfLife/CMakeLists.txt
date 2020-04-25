
project (ConwaysGameOfLife)
include_directories(src)
file(GLOB SOURCES "src/*.cpp")
add_executable(ConwaysGameOfLife ${SOURCES})

