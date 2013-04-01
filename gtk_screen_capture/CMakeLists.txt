cmake_minimum_required(VERSION 2.8)

project(screen_capture)
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")
add_executable(screen_capture screen_capture_snatch_view.cpp screen_capture_event.cpp screen_capture_model.cpp screencapture.cpp dialogflow.cpp mainflow.cpp main.cpp flow.cpp)

include_directories(/usr/include/glib-2.0)
include_directories(/usr/include/gio-unix-2.0)
include_directories(/usr/include/gtk-2.0)
include_directories(/usr/lib/i386-linux-gnu/gtk-2.0/include)
include_directories(/usr/include/pixman-1)
include_directories(/usr/lib/i386-linux-gnu/glib-2.0/include)
include_directories(/usr/include/cairo)
include_directories(/usr/include/atk-1.0)
include_directories(/usr/include/gdk-pixbuf-2.0)
include_directories(/usr/include/pango-1.0)
include_directories(/usr/include/freetype2)
#-lgtk-x11-2.0 -lgdk-x11-2.0 -latk-1.0 -lgio-2.0 -lpangoft2-1.0 -lpangocairo-1.0 -lgdk_pixbuf-2.0 -lcairo -lpango-1.0 -lfreetype -lfontconfig -lgobject-2.0 -lglib-2.0 

target_link_libraries(screen_capture -lgtk-x11-2.0 -lgdk-x11-2.0 -latk-1.0 -lgio-2.0 
-lpangoft2-1.0 -lpangocairo-1.0 -lgdk_pixbuf-2.0 -lpango-1.0 -lfreetype -lfontconfig -lgobject-2.0 -lglib-2.0)

install(TARGETS screen_capture RUNTIME DESTINATION bin)
