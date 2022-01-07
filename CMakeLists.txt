set(LIB_NAME ring_buffer_lib)

message(STATUS "Build: ${LIB_NAME}")

include_directories("src/inc")
file(GLOB_RECURSE LIB_SOURCES "src/*.*")

ADD_LIBRARY(${LIB_NAME} STATIC ${LIB_SOURCES})