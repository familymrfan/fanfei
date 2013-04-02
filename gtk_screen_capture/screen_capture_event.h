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


#ifndef WISP_WEBMAIL_CORE_SCREEN_CAPTURE_EVENT_H
#define WISP_WEBMAIL_CORE_SCREEN_CAPTURE_EVENT_H

#include "gtk/gtk.h"
#include "screen_capture_type.h"
#include <cstring>

typedef struct EVENTDRAGINFO
{
    custom_rect drag_rect;
    custom_point begin_point;
    custom_point move_point;
    int  offset_x;
    int  offset_y;
}EVENTDRAGINFO;

enum EventID
{
    EVENT_LEFT_BUTTON_DOWN, // POINT
    EVENT_LEFT_BUTTON_UP,   // POINT
    EVENT_DRAG,             // DRAGINFO
    EVENT_DRAG_OVER         // DRAGINFO
};
enum EventType
{
    EVENT_MOUSE,
    EVENT_KEY
};
class Event
{
    enum{ MAX_EVENT_PARAM_LEN = 1024};
public:
    Event(){}
    Event(EventID _event_id,EventType _event_type,void *data,int _length)
        :id_(_event_id),type_(_event_type){
        MakeParam(data,_length);
    }
    void MakeEvent(EventID _event_id,EventType _event_type,void *data,int _length){
        id_   = _event_id;
        type_ = _event_type;
        MakeParam(data,_length);
    }
    void GetParam(void *data,int &_length){
        std::memcpy(data,param_,length_);
        _length = length_;
    }
    EventID id_;
    EventType type_;
private:
    char    param_[MAX_EVENT_PARAM_LEN];
    int     length_;
    void MakeParam(void *data,int _length){
        std::memcpy(param_,data,_length);
        length_ = _length;
    }
};
class EventHandle
{
    virtual void OnEvent(Event event) = 0;
};

#endif // WISP_WEBMAIL_CORE_SCREEN_CAPTURE_EVENT_H