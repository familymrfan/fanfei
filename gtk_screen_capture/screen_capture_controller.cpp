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
#include <functional>
#include "screen_capture_controller.h"
#include "screen_capture_model.h"
#include "screen_capture_snatch_view.h"

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
} // namespace

// onpaint
gint OnPaint(GtkWidget *widget,GdkEvent  *event, gpointer callback_data)
{
  auto scc = static_cast<ScreenCaptureController *>(callback_data);
  auto cr = gdk_cairo_create(widget->window);
  cairo_set_source_rgb(cr,0.0f,0.0f,0.0f);
  cairo_paint(cr);
  gdk_cairo_set_source_pixbuf(cr,scc->desktop_image_pixbuf_,0,0);
  cairo_paint_with_alpha(cr,0.6f);
  cairo_destroy(cr);
  
  scc->snatch_view_->Paint();
  
  return false;
}

gint OnLButtonDownMessage(GtkWidget *widget,GdkEvent  *event,gpointer callback_data){
    auto scc = static_cast<ScreenCaptureController *>(callback_data);
    if(scc == nullptr){
      return false;
    }
    scc->is_drag_ = true;
    scc->start_point_.x = scc->end_point_.x = event->button.x; 
    scc->start_point_.y = scc->end_point_.y = event->button.y;
    Event _event;
    _event.MakeEvent(EVENT_LEFT_BUTTON_DOWN,EVENT_MOUSE,static_cast<void *>(&scc->start_point_),sizeof(custom_point));
    scc->DispatchEvent(_event);
    return true;
}

gint OnLButtonUpMessage(GtkWidget *widget,GdkEvent *event,gpointer callback_data){
    auto scc = static_cast<ScreenCaptureController *>(callback_data);
    if(scc == nullptr){
      return false;
    }
    if(true == scc->is_drag_){
        scc->end_point_.x = event->button.x;
        scc->end_point_.y = event->button.y;
        // build rect
        custom_rect rect;
        rect.left   = scc->start_point_.x;
        rect.top    = scc->start_point_.y;
        rect.right  = scc->end_point_.x;
        rect.bottom = scc->end_point_.y;
        if(scc->start_point_.x>scc->end_point_.x){
            std::swap(rect.left,rect.right);
        }
        if(scc->start_point_.y>scc->end_point_.y){
            std::swap(rect.top,rect.bottom);
        }
        EVENTDRAGINFO drag_info = {rect,scc->start_point_,scc->end_point_,
	  scc->end_point_.x-scc->start_point_.x,scc->end_point_.y-scc->start_point_.y};
        Event event;
        event.MakeEvent(EVENT_DRAG_OVER,EVENT_MOUSE,static_cast<void *>(&drag_info),sizeof(EVENTDRAGINFO));
        scc->DispatchEvent(event);
        scc->is_drag_ = false;
    }
    Event _event;
    _event.MakeEvent(EVENT_LEFT_BUTTON_UP,EVENT_MOUSE,static_cast<void *>(&scc->end_point_),sizeof(custom_point));
    scc->DispatchEvent(_event);
    return true;
}
gint OnMouseMoveMessage(GtkWidget *widget,GdkEvent *event,gpointer callback_data){
    auto scc = static_cast<ScreenCaptureController *>(callback_data);
    if(scc == nullptr){
      return false;
    }
    if(scc->is_drag_){
      int _x_offset = event->motion.x - scc->end_point_.x;
      int _y_offset = event->motion.y - scc->end_point_.y;
      scc->end_point_.x = event->motion.x;
      scc->end_point_.y = event->motion.y;
      // build rect
      custom_rect rect;
      rect.left   = scc->start_point_.x;
      rect.top    = scc->start_point_.y;
      rect.right  = scc->end_point_.x;
      rect.bottom = scc->end_point_.y;
      if(scc->start_point_.x>scc->end_point_.x){
          std::swap(rect.left,rect.right);
      }
      if(scc->start_point_.y>scc->end_point_.y){
          std::swap(rect.top,rect.bottom);
      }
      EVENTDRAGINFO drag_info = {rect,scc->start_point_,scc->end_point_,_x_offset,_y_offset};
      Event _event;
      _event.MakeEvent(EVENT_DRAG,EVENT_MOUSE,static_cast<void *>(&drag_info),sizeof(EVENTDRAGINFO));
      scc->DispatchEvent(_event);
    }
    return true;
}

void ScreenCaptureController::Init(){
    auto window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_realize (window);
    
    auto darea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER (window), darea);
    
    gtk_window_fullscreen(GTK_WINDOW(window));
    gtk_widget_add_events(window, GDK_BUTTON_PRESS_MASK|GDK_BUTTON_RELEASE_MASK|GDK_POINTER_MOTION_MASK);
    
    desktop_image_pixbuf_ = get_screenshot();
    
    g_signal_connect(darea, "expose_event", G_CALLBACK(OnPaint), this);
    g_signal_connect(window, "button_press_event", G_CALLBACK(OnLButtonDownMessage), this);
    g_signal_connect(window, "button_release_event", G_CALLBACK(OnLButtonUpMessage), this);
    g_signal_connect(window, "motion_notify_event", G_CALLBACK(OnMouseMoveMessage), this);
    g_signal_connect(window, "key_press_event", G_CALLBACK(gtk_main_quit), nullptr);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), nullptr);
    gtk_widget_show_all(window);
    
    
    //model and capture view
    model_ = std::make_shared<ScreenCaptureModel>(gtk_image_new_from_pixbuf(desktop_image_pixbuf_));
    snatch_view_ = std::make_shared<ScreenCaptureSnatchView>(darea->window);
    model_->SetSnatchView(snatch_view_.get());
    snatch_view_->SetModel(model_.get());

    //auth
    snatch_view_->GetAuth(AUTH_REDRAW_ALL_VIEWS,[window](){gdk_window_invalidate_rect(window->window,NULL,true); });
}

bool ScreenCaptureController::Operate(){
    Init();
    return true;
}

void ScreenCaptureController::DispatchEvent(Event event){
    model_->OnEvent(event);
    snatch_view_->OnEvent(event);
}