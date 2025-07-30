# ./CMakeLists.txt
#cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=path
cmake_minimum_required(VERSION 3.14...3.27)
project(SnakeGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


find_package(Qt5 REQUIRED COMPONENTS Widgets)
find_package(spdlog CONFIG REQUIRED)

set(SOURCES
    src/run.cpp
    src/main_window.cpp
    src/base_page_widget.cpp
    src/main_widget.cpp
    src/game_widget.cpp
    src/option_widget.cpp
    src/ui_factory.cpp
    src/language_manager.cpp
    src/settings_manager.cpp
    src/log_manager.cpp
)

qt5_wrap_cpp(MOC_SOURCES 
    include/main_window.hpp
    include/base_page_widget.hpp
    include/main_widget.hpp
    include/game_widget.hpp
    include/option_widget.hpp
    include/ui_factory.hpp
    include/language_manager.hpp
    include/settings_manager.hpp
    include/log_manager.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${MOC_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_definitions(${PROJECT_NAME} PRIVATE SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE)


qt_add_resources(SnakeGame_RESOURCES resources.qrc)

target_sources(${PROJECT_NAME} PRIVATE ${SnakeGame_RESOURCES})
 

target_link_libraries(${PROJECT_NAME} Qt5::Widgets spdlog::spdlog)

