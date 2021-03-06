cmake_minimum_required(VERSION 2.8)

set(PLAYERPLATFORM_PLUGIN_NAME PlayerPlatform)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

message("Building QAM Streamer....")

find_package(Broadcast REQUIRED)

set(PLAYERPLATFORM_PLUGIN_SOURCES PlayerImplementation.cpp)

set(PLAYERPLATFORM_PLUGIN_LIBS ${LIBBROADCAST_LIBRARIES})

set(PLAYERPLATFORM_PLUGIN_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} ${WPEFRAMEWORK_INCLUDE_DIRS})

if (WPEFRAMEWORK_PLUGIN_STREAMER_TS_SCANNING)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DENABLE_TS_SCANNING")
endif(WPEFRAMEWORK_PLUGIN_STREAMER_TS_SCANNING)


# add the library
set(ADDITIONAL_LIBRARIES ${PLAYERPLATFORM_PLUGIN_LIBS} PARENT_SCOPE)
add_library(${PLAYERPLATFORM_PLUGIN_NAME} STATIC ${PLAYERPLATFORM_PLUGIN_SOURCES})
target_compile_definitions(${PLAYERPLATFORM_PLUGIN_NAME} PRIVATE ${PLAYERPLATFORM_PLUGIN_DEFINITIONS})
target_include_directories(${PLAYERPLATFORM_PLUGIN_NAME} PRIVATE ${PLAYERPLATFORM_PLUGIN_INCLUDE_DIRS})
target_link_libraries(${PLAYERPLATFORM_PLUGIN_NAME} ${LIBNXCLIENT_LIBRARY} ${LIBNEXUS_LIBRARY})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

install(TARGETS ${PLAYERPLATFORM_PLUGIN_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/)
