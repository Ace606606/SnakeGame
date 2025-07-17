# ./CMakeLists.txt
cmake_minimum_required(VERSION 3.14...3.27)
project(SnakeGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


find_package(Qt5 REQUIRED COMPONENTS Widgets)

set(SOURCES
    src/run.cpp
    src/mainWindow.cpp
    src/mainWidget.cpp
    src/gameWidget.cpp
    src/optionWidget.cpp
)

qt5_wrap_cpp(MOC_SOURCES 
    include/mainWindow.hpp
    include/mainWidget.hpp
    include/gameWidget.hpp
    include/optionWidget.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${MOC_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

qt_add_resources(SnakeGame_RESOURCES resources.qrc)

target_sources(${PROJECT_NAME} PRIVATE ${SnakeGame_RESOURCES})
 

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

#configure_file(${CMAKE_SOURCE_DIR}/style/style.qss style/style.qss COPYONLY)