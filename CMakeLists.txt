cmake_minimum_required(VERSION 3.20)
project(logicario)

find_package(spdlog CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(crossguid CONFIG REQUIRED)

file(GLOB_RECURSE sources "source/*.hpp" "source/*.cpp")

add_executable(${PROJECT_NAME} ${sources})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED true)

target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog glfw crossguid)
target_include_directories(${PROJECT_NAME} PRIVATE source/)