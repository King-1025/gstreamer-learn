#扫描目录"."内的源文件
aux_source_directory (. DIR_SRCS)                #添加可执行文件
add_executable (test ${DIR_SRCS})
set(CMAKE_C_FLAGS "-pthread -Wall -O3")
#将目标和库文件连接
include_directories(/data/data/com.termux/files/usr/include/gstreamer-1.0 /data/data/com.termux/files/usr/include/glib-2.0 /data/data/com.termux/files/usr/lib/glib-2.0/include /data/data/com.termux/files/usr/include)
link_directories(/data/data/com.termux/files/usr/lib)
target_link_libraries (test -lgstreamer-1.0 -lgobject-2.0 glib-2.0)
#安装目标到最终路径
install (TARGETS test RUNTIME DESTINATION bin)
#添加子目录
#add_subdirectory (demo)
#add_subdirectory (tools)
