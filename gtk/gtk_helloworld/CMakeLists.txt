cmake_minimum_required (VERSION 2.8)
project (HelloWorld)

link_directories(d:/gtk/lib)

add_executable(HelloWorld hello_world.cpp)

set_target_properties(HelloWorld PROPERTIES LINK_FLAGS "/SUBSYSTEM:windows")



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

target_link_libraries(HelloWorld gtk-win32-2.0.lib gdk-win32-2.0.lib atk-1.0.lib gio-2.0.lib pangowin32-1.0.lib gdi32.lib pangocairo-1.0.lib gdk_pixbuf-2.0.lib pango-1.0.lib cairo.lib gobject-2.0.lib 
gmodule-2.0.lib gthread-2.0.lib glib-2.0.lib intl.lib)
