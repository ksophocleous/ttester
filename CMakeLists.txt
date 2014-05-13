cmake_minimum_required(VERSION 2.8)

project(ttester CXX)

set(version_major "0")
set(version_minor "7")
set(version_patch "0")

set(src
	"src/ttester.cpp"
	"src/tsuite.cpp"
	"src/logger.cpp")

set(public_hdr_loc "include/ttester")
set(public_hdrs
	"${public_hdr_loc}/core.h"
	"${public_hdr_loc}/trunner.h"
	"${public_hdr_loc}/tsuite.h"
	"${public_hdr_loc}/ttester.h"
	"${public_hdr_loc}/tsuite_exception.h"
	"${public_hdr_loc}/logger.h")

#--------------------------------------------------------

list(APPEND platformlibs "")
list(APPEND include_directories "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_library(ttester ${src} ${public_hdrs})
set_target_properties(ttester PROPERTIES
	PUBLIC_HEADER "${public_hdrs}"
	INCLUDE_DIRECTORIES "${include_directories}"
	VERSION "${version_major}.${version_minor}.${version_patch}"
#	SOVERSION "${version_major}"
)
target_link_libraries(ttester ${platformlibs})

install(TARGETS ttester
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	PUBLIC_HEADER DESTINATION ${public_hdr_loc})
