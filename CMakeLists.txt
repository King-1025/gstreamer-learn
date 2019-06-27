#检查cmake版本需求
cmake_minimum_required (VERSION 2.8)
#工程名称:gst-learn
project(gst-learn C CXX)
#设置目标输出路径,注:PROJECT_BINARY_DIR指编译发生的目录册
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
#设置安装路径前缀
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/result)
#安装其他文件
#INSTALL(FILES COPYRIGHT README.md DESTINATION share/docs/${PROJECT_NAME})
#INSTALL(DIRECTORY docs/ DESTINATION share/docs/${PROJECT_NAME})
#添加包含源文件的子目录"src"
add_subdirectory (test)
add_subdirectory (src)
