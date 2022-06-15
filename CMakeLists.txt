# CMake 最低版本号要求
cmake_minimum_required(VERSION 3.0)

# 项目名称
project(test_plugin_system)

# C++版本
set(CMAKE_CXX_STANDARD 20)

# 设置动态库的输出目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
# 设置静态库的输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
# 设置可执行文件的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# 添加子目录
add_subdirectory(boost_plugin_system/plugin)
add_subdirectory(boost_plugin_system/application)

add_subdirectory(poco_plugin_system/plugin)
add_subdirectory(poco_plugin_system/application)

add_subdirectory(ogre_plugin_system/plugin)
add_subdirectory(ogre_plugin_system/application)
