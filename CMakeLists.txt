cmake_minimum_required(VERSION 3.12)

project (DominicTorrento)

set(PROJECT_NAME main)


set(INCLUDES
	includes/BencodeReader.hpp
	includes/PrettyPrinter.hpp
	includes/Values.hpp
)

set(SOURCE_EXE
	src/main.cpp
)


set(SOURCES
	src/BencodeReader.cpp
	src/PrettyPrinter.cpp
	src/Values.cpp
)

set (TORRENT_FILES
	torrent/sample2.torrent
	)

set(ALL_SOURCES
	${INCLUDES}
	${SOURCES}
	${TORRENT_FILES}
)

add_library(BencodeReader STATIC
${ALL_SOURCES}
)

target_include_directories(BencodeReader PUBLIC includes)
target_include_directories(BencodeReader PRIVATE src)
target_include_directories(BencodeReader PRIVATE torrent)

 
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES 
	${ALL_SOURCES}
)

add_executable(${PROJECT_NAME} ${SOURCE_EXE})

target_link_libraries(${PROJECT_NAME} BencodeReader)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
