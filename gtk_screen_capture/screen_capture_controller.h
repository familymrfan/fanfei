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


#ifndef SCREENCAPTURE_H
#define SCREENCAPTURE_H

#include <string>
#include <memory>
#include "flow.h"
#include "screen_capture_event.h"

enum AUTHLLIST
{
    AUTH_REDRAW_ALL_VIEWS
};

class ScreenCaptureModel;
class ScreenCaptureSnatchView;
class ScreenCaptureController : public Flow
{
public:
    ScreenCaptureController():desktop_image_pixbuf_(nullptr),width_(0),height_(0),is_drag_(false){

    }
protected:
  void Init();
  void DispatchEvent(Event event);
  bool WriteBitmapToFile();
  friend gint OnPaint(GtkWidget *widget, GdkEvent *event, gpointer callback_data);
  friend gint OnLButtonDownMessage(GtkWidget *widget,GdkEvent *event,gpointer callback_data);
  friend gint OnLButtonUpMessage(GtkWidget *widget,GdkEvent *event,gpointer callback_data);
  friend gint OnMouseMoveMessage(GtkWidget *widget,GdkEvent *event,gpointer callback_data);
  virtual bool Operate() override;
private:
    // model
    std::shared_ptr<ScreenCaptureModel> model_;
    // snatch view
    std::shared_ptr<ScreenCaptureSnatchView> snatch_view_;
    //desktop image
    GdkPixbuf *desktop_image_pixbuf_;
    // base
    int width_;
    int height_;
    // EVENT_DRAG_RECT assistant 
    bool is_drag_;
    custom_rect drag_rect_;
    custom_point start_point_;
    custom_point end_point_;
    // other
    std::string file_path_;
    
};

#endif // SCREENCAPTURE_H
