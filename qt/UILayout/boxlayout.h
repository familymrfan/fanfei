#ifndef BOX_LAYOUT_H_
#define BOX_LAYOUT_H_

#include "widget.h"
#include "layout.h"

namespace ui
{
class BoxLayout:public Layout
{
protected:
    virtual void Update()  {
        auto iter = layout_items_.begin();
        while(iter != layout_items_.end()) {
            LayoutItem *item = *iter;
            
            //¾ÓÖÐ
            int32_t width = item->PreferSize().width_, height = item->PreferSize().height_;
            int32_t x = (Width() - width)/2, y = (Height() - height)/2;
            
            if(item->IsValidGap(LayoutItem::kWestValid) && item->IsValidGap(LayoutItem::kEastValid)) {
                x = X() + item->WestSpace();
                width = Width() - item->EastSpace() - item->WestSpace();
            } else if(item->IsValidGap(LayoutItem::kWestValid)) {
                x = X() + item->WestSpace();
                width = item->PreferSize().width_;
            } else if(item->IsValidGap(LayoutItem::kEastValid)) {
                width = item->PreferSize().width_;
                x = X() + Width() - item->EastSpace() - width;
            }

            if(item->IsValidGap(LayoutItem::kNorthValid) && item->IsValidGap(LayoutItem::kSouthValid)) {
                y = Y() + item->NorthSpace();
                height = Height() - item->NorthSpace() - item->SouthSpace();
            } else if(item->IsValidGap(LayoutItem::kNorthValid)) {
                y = Y() + item->NorthSpace();
                height = item->PreferSize().height_;
            } else if(item->IsValidGap(LayoutItem::kSouthValid)) {
                height = item->PreferSize().height_;
                y = Y() + Height() - item->SouthSpace() - height;
            }

            item->SetGeometry(x, y, width, height);
            item->Update();
            iter++;
        }
    }
};

} // namespace ui

#endif // BOX_LATOUT_H_