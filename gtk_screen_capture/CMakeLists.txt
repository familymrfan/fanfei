cmake_minimum_required(VERSION 2.8)

project(screen_capture)
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")

if(LINUX)

elseif (WIN32)

link_directories(d:/gtk/lib)

endif()

add_executable(screen_capture screen_capture_type.cpp screen_capture_snatch_view.cpp screen_capture_event.cpp screen_capture_model.cpp screen_capture_controller.cpp dialogflow.cpp mainflow.cpp main.cpp flow.cpp)

if(LINUX)
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
elseif (WIN32)

set_target_properties(screen_capture PROPERTIES LINK_FLAGS "/SUBSYSTEM:windows")

#-mms-bitfields -Id:/gtk/include/gtk-2.0 -Id:/gtk/lib/gtk-2.0/include -Id:/gtk/in
#clude/atk-1.0 -Id:/gtk/include/cairo -Id:/gtk/include/gdk-pixbuf-2.0 -Id:/gtk/in
#clude/pango-1.0 -Id:/gtk/include/glib-2.0 -Id:/gtk/lib/glib-2.0/include -Id:/gtk
#/include -Id:/gtk/include/freetype2 -Id:/gtk/include/libpng14

include_directories(d:/gtk/include/gtk-2.0)
include_directories(d:/gtk/lib/gtk-2.0/include)
include_directories(d:/gtk/include/atk-1.0)
include_directories(d:/gtk/include/cairo)
include_directories(d:/gtk/include/gdk-pixbuf-2.0)
include_directories(d:/gtk/include/pango-1.0)
include_directories(d:/gtk/include/glib-2.0)
include_directories(d:/gtk/lib/glib-2.0/include)
include_directories(d:/gtk/include)
include_directories(d:/gtk/include/freetype2)
include_directories(d:/gtk/include/libpng14)

#-Ld:/gtk/lib -lgtk-win32-2.0 -lgdk-win32-2.0 -latk-1.0 -lgio-2.0 -lpangowin32-1.
#0 -lgdi32 -lpangocairo-1.0 -lgdk_pixbuf-2.0 -lpango-1.0 -lcairo -lgobject-2.0 -l
#gmodule-2.0 -lgthread-2.0 -lglib-2.0 -lintl

target_link_libraries(screen_capture gtk-win32-2.0.lib gdk-win32-2.0.lib atk-1.0.lib gio-2.0.lib pangowin32-1.0.lib gdi32.lib pangocairo-1.0.lib gdk_pixbuf-2.0.lib pango-1.0.lib cairo.lib gobject-2.0.lib 
gmodule-2.0.lib gthread-2.0.lib glib-2.0.lib intl.lib)

endif()

install(TARGETS screen_capture RUNTIME DESTINATION bin)
