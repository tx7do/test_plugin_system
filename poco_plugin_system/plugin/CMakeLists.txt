# CMake 最低版本号要求
cmake_minimum_required(VERSION 3.0)

# 项目名称
project(poco_plugin)

find_package(Poco REQUIRED Foundation)

# 包含include目录，里面都是头文件
include_directories(${Poco_INCLUDE_DIRS})

# 将 src 目录下的所有源文件加入后面的变量之中
aux_source_directory(. DIR_LIB_SRCS)

# 构建生成动态库
add_library(${PROJECT_NAME} SHARED ${DIR_LIB_SRCS})

# 指定目标链接的库
target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        dl
        rt
        pthread
        ${Poco_LIBRARIES}
        ${Boost_LIBRARIES}
)

