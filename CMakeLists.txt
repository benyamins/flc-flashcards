cmake_minimum_required(VERSION 3.18)

project(flashcard)
set(flc VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compiler options
if(MSVC)
	add_compile_options()
elseif(UNIX)
	add_compile_options(-Wall -Werror -Wextra -pedantic-errors -Wconversion -std=c++20)
endif()

add_executable(flc
	src/main.cpp
	src/console.cpp
)

find_package(fmt REQUIRED)
find_package(nlohmann_json REQUIRED)

target_link_libraries(flc
	fmt
	nlohmann_json
)

target_include_directories(flc PUBLIC
	"${PROJECT_BINARY_DIR}"
	"${PROJECT_SOURCE_DIR}/include"
)
