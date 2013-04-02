#include "screen_capture_type.h"

void CustomOffsetRect(custom_rect* pRect,int dx,int dy) {
  pRect->left+=dx;
  pRect->right+=dx;
  pRect->top+=dy;
  pRect->bottom+=dy;
}

void CustomSetRect(custom_rect* pRect,int left,int top,int right,int bottom){
  pRect->left = left;
  pRect->top = top;
  pRect->right =right;
  pRect->bottom = bottom;
}
  
bool CustomIsRectEmpty(const custom_rect* pRect){
  if(pRect->left == 0 && pRect->right == 0 || pRect->top == 0 && pRect->bottom == 0){
    return true;
  }else{
    return false;
  }
}

bool CustomPtInRect(const custom_rect* pRect,custom_point pt){
  if(pt.x>=pRect->left && pt.x<=pRect->right && pt.y>=pRect->top && pt.y<=pRect->bottom){
    return true;
  }else{
    return false;
  }
}