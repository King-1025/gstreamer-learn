
set(CMAKE_C_FLAGS "-pthread -Wall -O3")

add_executable (hello hello.c)
add_executable (rtsp-mp4 rtsp-mp4.c)
add_executable (rtsp-server rtsp-server.c)
add_executable (tutorial-1 tutorial-1.c)

set(TERMUX_INCLUDE "/data/data/com.termux/files/usr/include")

include_directories(${TERMUX_INCLUDE} ${TERMUX_INCLUDE}/gstreamer-1.0 ${TERMUX_INCLUDE}/glib-2.0 /data/data/com.termux/files/usr/lib/glib-2.0/include /data/data/com.termux/files/home/self/include/gstreamer-1.0)

set(COMMON_LIBS "-lgstreamer-1.0 -lgobject-2.0 -lglib-2.0")

set(RTSP_LIB "/data/data/com.termux/files/home/self/lib/libgstrtspserver-1.0.so")

target_link_libraries(tutorial-1 ${COMMON_LIBS})
target_link_libraries(rtsp-server ${COMMON_LIBS} ${RTSP_LIB})
target_link_libraries(rtsp-mp4 ${COMMON_LIBS} ${RTSP_LIB})
target_link_libraries(hello ${COMMON_LIBS})

#安装目标到最终路径
install (TARGETS hello rtsp-mp4 tutorial-1 RUNTIME DESTINATION bin)
