#ifndef WISP_WEBMAIL_CORE_SCREEN_CAPTURE_TYPE_H
#define WISP_WEBMAIL_CORE_SCREEN_CAPTURE_TYPE_H
#pragma once

typedef struct _custom_point {
    _custom_point():x(0),y(0){};
    int x, y;
}custom_point;

typedef struct _custom_rect {
    _custom_rect():left(0),top(0),right(0),bottom(0){}
    int left, top;
    int right, bottom;
}custom_rect;

void CustomOffsetRect(custom_rect* pRect,int dx,int dy);

void CustomSetRect(custom_rect* pRect,int left,int top,int right,int bottom);
  
bool CustomIsRectEmpty(const custom_rect* pRect);

bool CustomPtInRect(const custom_rect* pRect,custom_point pt);

#endif // WISP_WEBMAIL_CORE_SCREEN_CAPTURE_TYPE_H