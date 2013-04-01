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


#include "screen_capture_snatch_view.h"
#include "screen_capture_model.h"

#include <utility>

void ScreenCaptureSnatchView::Paint(){
    // draw capture snatch view 
    HDC mem_dc = CreateCompatibleDC(hdc);
    HBITMAP old_desktop_bitmap = static_cast<HBITMAP>(::SelectObject(mem_dc,model_->GetDesktopBitmap()));
    ::BitBlt(hdc,area_.left,area_.top,area_.right-area_.left,area_.bottom-area_.top,mem_dc,area_.left,area_.top,SRCCOPY);
    ::SelectObject(mem_dc,old_desktop_bitmap);
    ::DeleteDC(mem_dc);

    // draw border
    HBRUSH brush = ::CreateSolidBrush(model_->GetSnatchViewBorderColor());
    ::FrameRect(hdc,&area_,brush);
    //  draw corner rects
    RECT rect[STRETCH_END];
    MakeStrechCornerRects(rect);
    for (int i=STRETCH_LEFT_TOP;i<STRETCH_END;i++){
        ::FillRect(hdc,&rect[i],brush);
    }
    ::DeleteObject(brush);
    
}

void ScreenCaptureSnatchView::PostPanit(){
    UseAuth(AUTH_REDRAW_ALL_VIEWS);
}

void ScreenCaptureSnatchView::OnEvent(Event event){
    if(event.id_ == EVENT_DRAG 
        && event.type_ == EVENT_MOUSE){
            int length;
            EVENTDRAGINFO drag_info;
            event.GetParam(static_cast<void *>(&drag_info),length);
            if(!model_->IsCaptureOver()){
                area_ = drag_info.drag_rect;
                PostPanit();
            }
            else{
                if(model_->IsDrag()){
                    int screen_width  = GetSystemMetrics(SM_CXSCREEN);
                    int screen_height = GetSystemMetrics(SM_CYSCREEN);
                    OffsetRect(&area_,drag_info.offset_x,drag_info.offset_y);
                    if(area_.left<0){
                        area_.right = area_.right - area_.left;
                        area_.left = 0;
                    }
                    else if(area_.right>screen_width){
                        area_.left = screen_width - (area_.right - area_.left);
                        area_.right = screen_width;
                    }
                    if(area_.top<0){
                        area_.bottom = area_.bottom - area_.top;
                        area_.top = 0;
                    }
                    else if(area_.bottom>screen_height){
                        area_.top = screen_height - (area_.bottom - area_.top);
                        area_.bottom = screen_height;
                    }
                    PostPanit();
                }
                else{
                    STRETCH_TYPE strech_type;
                    if(STRETCH_NO != (strech_type = model_->GetStretchType())){
                        switch(strech_type)
                        {
                        case STRETCH_LEFT_TOP:
                            area_.left += drag_info.offset_x;
                            area_.top  += drag_info.offset_y;
                            if(area_.left>area_.right && area_.top>area_.bottom){
                                model_->SetStretchType(STRETCH_RIGHT_BOTTOM);
                            }
                            else{
                                if(area_.left>area_.right){
                                    model_->SetStretchType(STRETCH_RIGHT_TOP);
                                }
                                if(area_.top>area_.bottom){
                                    model_->SetStretchType(STRETCH_LEFT_BOTTOM);
                                }
                            }
                            break;
                        case STRETCH_TOP:
                            area_.top  += drag_info.offset_y;
                            if(area_.top>area_.bottom){
                                model_->SetStretchType(STRETCH_BOTTOM);
                            }
                            break;
                        case STRETCH_RIGHT_TOP:
                            area_.right += drag_info.offset_x;
                            area_.top  += drag_info.offset_y;
                            if(area_.left>area_.right && area_.top>area_.bottom){
                                model_->SetStretchType(STRETCH_LEFT_BOTTOM);
                            }
                            else{
                                if(area_.left>area_.right){
                                    model_->SetStretchType(STRETCH_LEFT_TOP);
                                }
                                if(area_.top>area_.bottom){
                                    model_->SetStretchType(STRETCH_RIGHT_BOTTOM);
                                }
                            }
                            break;
                        case STRETCH_LEFT:
                            area_.left += drag_info.offset_x;
                            if(area_.left>=area_.right){
                                model_->SetStretchType(STRETCH_RIGHT);
                            }
                            break;
                        case STRETCH_RIGHT:
                            area_.right += drag_info.offset_x;
                            if(area_.left>area_.right){
                                model_->SetStretchType(STRETCH_LEFT);
                            }
                            break;
                        case STRETCH_LEFT_BOTTOM:
                            area_.left += drag_info.offset_x;
                            area_.bottom  += drag_info.offset_y;
                            if(area_.left>area_.right && area_.top>area_.bottom){
                                model_->SetStretchType(STRETCH_RIGHT_TOP);
                            }
                            else{
                                if(area_.left>area_.right){
                                    model_->SetStretchType(STRETCH_RIGHT_BOTTOM);
                                }
                                if(area_.top>area_.bottom){
                                    model_->SetStretchType(STRETCH_LEFT_TOP);
                                }
                            }
                            break;
                        case STRETCH_BOTTOM:
                            area_.bottom  += drag_info.offset_y;
                            if(area_.top>area_.bottom){
                                model_->SetStretchType(STRETCH_TOP);
                            }
                            break;
                        case STRETCH_RIGHT_BOTTOM:
                            area_.right += drag_info.offset_x;
                            area_.bottom  += drag_info.offset_y;
                            if(area_.left>area_.right && area_.top>area_.bottom){
                                model_->SetStretchType(STRETCH_LEFT_TOP);
                            }
                            else{
                                if(area_.left>area_.right){
                                    model_->SetStretchType(STRETCH_LEFT_BOTTOM);
                                }
                                if(area_.top>area_.bottom){
                                    model_->SetStretchType(STRETCH_RIGHT_TOP);
                                }
                            }
                            break;
                        }
                        if(area_.left>area_.right){
                            std::swap(area_.left,area_.right);
                        }
                        if(area_.top>area_.bottom){
                            std::swap(area_.top,area_.bottom);
                        }
                        PostPanit();
                    }
                }
            }
    }
    else if(event.id_ == EVENT_DRAG_OVER
        && event.type_ == EVENT_MOUSE){
            if(!model_->IsCaptureOver()){
                if(!IsRectEmpty (&area_)){
                    model_->SetCaptureOver();
                }
            }
            model_->SetDrag(false);
            model_->SetStretchType(STRETCH_NO);
    }
    else if(event.id_ == EVENT_LEFT_BUTTON_DOWN
        && event.type_ == EVENT_MOUSE){
            int length;
            POINT pt;
            event.GetParam(static_cast<void *>(&pt),length);
            // stretch
            RECT rect[STRETCH_END];
            MakeStrechCornerRects(rect);
            for(int i=STRETCH_LEFT_TOP;i<STRETCH_END;i++){
                if(PtInRect(&rect[i],pt)){
                    model_->SetStretchType(static_cast<STRETCH_TYPE>(i));
                    return;
                }
            }
            // drag
            if(PtInRect(&area_,pt) && model_->IsCaptureOver()){
                model_->SetDrag();
            }
    }
    else if(event.id_ == EVENT_LEFT_BUTTON_UP
        && event.type_ == EVENT_MOUSE){
        model_->SetDrag(false);
        model_->SetStretchType(STRETCH_NO);
    }
}

void ScreenCaptureSnatchView::MakeStrechCornerRects(RECT rect[STRETCH_END]){
    int horizontal_half_width = (area_.right - area_.left)/2;
    int horizontal_width      = area_.right - area_.left;
    int vertical_half_width   = (area_.bottom - area_.top)/2;
    int vertical_width        = area_.bottom - area_.top;
    // left top
    SetRect(&rect[STRETCH_LEFT_TOP],
        area_.left - model_->GetStretchResponseWidth(),
        area_.top  - model_->GetStretchResponseWidth(),
        area_.left + model_->GetStretchResponseWidth(),
        area_.top  + model_->GetStretchResponseWidth()
        );
    // top
    rect[STRETCH_TOP] = rect[STRETCH_LEFT_TOP];
    OffsetRect(&rect[STRETCH_TOP],horizontal_half_width,0);
    // right top
    rect[STRETCH_RIGHT_TOP] = rect[STRETCH_LEFT_TOP];
    OffsetRect(&rect[STRETCH_RIGHT_TOP],horizontal_width,0);
    // left
    rect[STRETCH_LEFT] = rect[STRETCH_LEFT_TOP];
    OffsetRect(&rect[STRETCH_LEFT],0,vertical_half_width);
    // right
    rect[STRETCH_RIGHT] = rect[STRETCH_LEFT];
    OffsetRect(&rect[STRETCH_RIGHT],horizontal_width,0);
    // bottom left
    rect[STRETCH_LEFT_BOTTOM] = rect[STRETCH_LEFT_TOP];
    OffsetRect(&rect[STRETCH_LEFT_BOTTOM],0,vertical_width);
    // bottom
    rect[STRETCH_BOTTOM] = rect[STRETCH_TOP];
    OffsetRect(&rect[STRETCH_BOTTOM],0,vertical_width);
    // bottom right
    rect[STRETCH_RIGHT_BOTTOM] = rect[STRETCH_RIGHT_TOP];
    OffsetRect(&rect[STRETCH_RIGHT_BOTTOM],0,vertical_width);
}