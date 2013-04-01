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


#ifndef WISP_WEBMAIL_CORE_SCREEN_CAPTURE_SNATCH_VIEW_H
#define WISP_WEBMAIL_CORE_SCREEN_CAPTURE_SNATCH_VIEW_H
#pragma once

#include "gtk/gtk.h"
#include "screen_capture_controller.h"
#include "screen_capture_event.h"
#include "screen_capture_authmap.h"

class ScreenCaptureModel;

class ScreenCaptureSnatchView:public EventHandle,public AuthMap
{
    friend class ScreenCaptureController;
public:
    ScreenCaptureSnatchView(HDC _hdc):hdc(_hdc),model_(nullptr){
        SetRectEmpty(&area_) ;
    }
    void SetModel(ScreenCaptureModel *_sc_model){
        model_ = _sc_model;
    }
    RECT GetArea() {
        return area_;
    }
public:
    // paint alone
    void Paint();
    // Post Controller to paint all views
    void PostPanit();
    virtual void OnEvent(Event event) override;
protected:
    void MakeStrechCornerRects(GdkRegion rect[]);
private:
    HDC hdc;
    ScreenCaptureModel *model_;
    GdkRegion area_;
};

#endif // WISP_WEBMAIL_CORE_SCREEN_CAPTURE_SNATCH_VIEW_H

