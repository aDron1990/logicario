cmake_minimum_required(VERSION 3.20)
project(logicario)

find_package(spdlog CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(crossguid CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Stb REQUIRED)

file(GLOB_RECURSE sources "sources/*.hpp" "sources/*.cpp")

add_executable(${PROJECT_NAME} ${sources})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED true)
target_compile_definitions(${PROJECT_NAME} PRIVATE SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw GLEW::GLEW glm::glm spdlog::spdlog crossguid)
target_include_directories(${PROJECT_NAME} PRIVATE sources/ ${Stb_INCLUDE_DIR})