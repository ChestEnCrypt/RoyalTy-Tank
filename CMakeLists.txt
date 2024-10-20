cmake_minimum_required(VERSION 3.16)
project("RoyalTy-Tank")

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set output directories for executable files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})

# Set intermediate directory (optional)
set(CMAKE_INTERMEDIATE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/Intermediate)

# Add the source files
set(SOURCES
	src/main.cpp
	src/Button.cpp
)
add_executable("RoyalTy-Tank" ${SOURCES})

# Set the project as the default target for running
set_target_properties("RoyalTy-Tank" PROPERTIES FOLDER "Executable")

# Manually specify the SFML directory containing sfml-config.cmake
set(SFML_DIR "${CMAKE_SOURCE_DIR}/lib/cmake/SFML")

# Find SFML
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

# Link SFML libraries
target_link_libraries("RoyalTy-Tank" sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

# Add include directories for SFML
target_include_directories("RoyalTy-Tank" PRIVATE "${CMAKE_SOURCE_DIR}/include/SFML")

# Add include my personal directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Copy the dll folder to the executable's working directory
add_custom_command(TARGET "RoyalTy-Tank" POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/bin $<TARGET_FILE_DIR:RoyalTy-Tank>)

# Copy the assets folder to the executable's working directory
add_custom_command(TARGET "RoyalTy-Tank" POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:RoyalTy-Tank>/assets)
