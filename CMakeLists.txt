cmake_minimum_required(VERSION 3.16)
project("RoyalTy-Tank")

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the source files
add_executable("RoyalTy-Tank" src/main.cpp)

# Manually specify the SFML directory containing sfml-config.cmake
set(SFML_DIR "lib/cmake/SFML")

# Find SFML
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

# Link SFML libraries
target_link_libraries("RoyalTy-Tank" sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

# Add include directories for SFML
target_include_directories("RoyalTy-Tank" PRIVATE "${CMAKE_SOURCE_DIR}/include/SFML")

# Copy the dll folder to the executable's working directory
add_custom_command(TARGET "RoyalTy-Tank" POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/bin $<TARGET_FILE_DIR:RoyalTy-Tank>)

add_custom_command(TARGET RoyalTy-Tank POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:RoyalTy-Tank>/assets)