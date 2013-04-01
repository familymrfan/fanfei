/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) 2013  <copyright holder> <email>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "gtk/gtk.h"
#include <iostream>
#include "screen_capture_controller.h"

namespace
{
GdkPixbuf * get_screenshot(){
    gint x_orig, y_orig;
    gint width, height;
    auto root_window = gdk_get_default_root_window ();
    gdk_drawable_get_size (root_window, &width, &height);      
    gdk_window_get_origin (root_window, &x_orig, &y_orig);
    auto screenshot = gdk_pixbuf_get_from_drawable (NULL, root_window, NULL,
                                           x_orig, y_orig, 0, 0, width, height);
    return screenshot;
}
gboolean expose(GtkWidget *widget, GdkEventExpose *event, gpointer userdata)
{
  auto cr = gdk_cairo_create(widget->window);
  cairo_set_source_rgb(cr,0.0f,0.0f,0.0f);
  cairo_paint(cr);
  gdk_cairo_set_source_pixbuf(cr,static_cast<GdkPixbuf *>(userdata),0,0);
  cairo_paint_with_alpha(cr,0.6f);
  cairo_destroy(cr);
  return FALSE;
}
} // namespace

void ScreenCaptureController::Init(){
    auto window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_realize (window);
    auto darea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER (window), darea);
    gtk_window_fullscreen(GTK_WINDOW(window));
    g_signal_connect(darea, "expose_event", G_CALLBACK(expose), get_screenshot());
    g_signal_connect (window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all (window);
}

bool ScreenCaptureController::Operate(){
    Init();
    return true;
}

