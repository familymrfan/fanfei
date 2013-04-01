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


#ifndef WISP_WEBMAIL_CORE_SCREEN_CAPTURE_MODEL_H
#define WISP_WEBMAIL_CORE_SCREEN_CAPTURE_MODEL_H
#pragma once

#include "gtk/gtk.h"
#include "screen_capture_event.h"

enum STRETCH_TYPE
{
    STRETCH_NO = -1,
    STRETCH_LEFT_TOP,
    STRETCH_TOP,
    STRETCH_RIGHT_TOP,
    STRETCH_LEFT,
    STRETCH_RIGHT,
    STRETCH_LEFT_BOTTOM,
    STRETCH_BOTTOM,
    STRETCH_RIGHT_BOTTOM,
    STRETCH_END
};

class ScreenCaptureSnatchView;

class ScreenCaptureModel:public EventHandle
{
public:
    ScreenCaptureModel(HBITMAP _desktop_bitmap)
        :desktop_bitmap_(_desktop_bitmap),is_capture_over_(false),
        is_drag_(false),snatch_view_(nullptr),strech_type_(STRETCH_NO),
        stretch_response_width_(3),snatch_view_border_width_(1),snatch_view_border_color_(RGB(65,105,225)){}

    void SetSnatchView(ScreenCaptureSnatchView *_sc_snatch_view){
        snatch_view_ = _sc_snatch_view;
    }
public:
    void SetCaptureOver(bool _is_capture_over = true){
        is_capture_over_ = _is_capture_over;
    }
    bool IsCaptureOver() const{
        return is_capture_over_;
    }
    void SetDrag(bool _is_drag = true){
        is_drag_ = _is_drag;
    }
    bool IsDrag() const{
        return is_drag_;
    }
    void SetStretchType(STRETCH_TYPE _strech_type){
        strech_type_ = _strech_type;
    }
    STRETCH_TYPE GetStretchType() const{
        return strech_type_;
    }
    int GetStretchResponseWidth() const{
        return stretch_response_width_;
    }
    int GetSnatchViewBorderWidth() const{
        return stretch_response_width_;
    }
    GdkColor* GetSnatchViewBorderColor() const{
        return snatch_view_border_color_;
    }
    /*HBITMAP GetDesktopBitmap() const{
        return desktop_bitmap_;
    }*/
    virtual void OnEvent(Event event) override{

    }
private:
    //HBITMAP desktop_bitmap_;
    bool    is_drag_;
    bool    is_capture_over_;
    STRETCH_TYPE strech_type_;
    int     stretch_response_width_; // read only
    int     snatch_view_border_width_; // read only
    GdkColor* snatch_view_border_color_; // read only
    ScreenCaptureSnatchView *snatch_view_;
};

#endif // WISP_WEBMAIL_CORE_SCREEN_CAPTURE_MODEL_H    


