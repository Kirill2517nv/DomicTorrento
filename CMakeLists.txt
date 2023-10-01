cmake_minimum_required(VERSION 3.12)

project (DominicTorrento)

set(PROJECT_NAME main)

set (BOOST_ROOT "A:/GitHub/DominicTorrento/external/boost_1_82_0") # Путь к библиотеке Boost
  
set (Boost_NO_SYSTEM_PATHS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_STATIC_RUNTIME OFF)
set (BOOST_ALL_DYN_LINK OFF)
find_package (Boost REQUIRED COMPONENTS REQUIRED)

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

set(ALL_SOURCES
	${INCLUDES}
	${SOURCES}
)

add_library(BencodeReader STATIC
${ALL_SOURCES}
)

target_include_directories(BencodeReader PUBLIC includes)
target_include_directories(BencodeReader PRIVATE src)

 
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES 
	${ALL_SOURCES}
)
if (Boost_FOUND)
	include_directories (SYSTEM ${Boost_INCLUDE_DIR}) # подключаем заголовочные файлы
	add_executable(${PROJECT_NAME} ${SOURCE_EXE})
    target_link_libraries (${PROJECT_NAME} ${Boost_LIBRARIES}) # подключаем библиотеку
endif ()

target_link_libraries(${PROJECT_NAME} BencodeReader)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
