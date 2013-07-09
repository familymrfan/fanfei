#ifndef BOX_LAYOUT_H_
#define BOX_LAYOUT_H_

#include "widget.h"
#include "layout.h"
#include <algorithm>

namespace ui
{
class BoxLayout:public Layout
{
public:
    virtual void AddItem(LayoutItem *item) {
        Layout::AddItem(item);
    }
protected:
    virtual void Update()  {
        auto iter = layout_items_.begin();
        while(iter != layout_items_.end()) {
            LayoutItem *item = *iter;
            
            //¾ÓÖÐ
            int32_t width = std::min(item->PreferSize().width_, Width()), height = std::min(item->PreferSize().height_, Height());
            int32_t x = (Width() - width)/2, y = (Height() - height)/2;
            
            if(item->IsValidGap(LayoutItem::kWestValid) && item->IsValidGap(LayoutItem::kEastValid)) {
                x = X() + item->WestSpace();
                width = Width() - item->EastSpace() - item->WestSpace();
            } else {
                if(item->IsValidGap(LayoutItem::kWestValid)) {
                    width = std::min(item->PreferSize().width_, Width() - item->WestSpace());
                    x = X() + item->WestSpace();
                } else if(item->IsValidGap(LayoutItem::kEastValid)) {
                    width = std::min(item->PreferSize().width_, Width() - item->EastSpace());
                    x = X() + Width() - item->EastSpace() - width;
                }
            }

            if(item->IsValidGap(LayoutItem::kNorthValid) && item->IsValidGap(LayoutItem::kSouthValid)) {
                y = Y() + item->NorthSpace();
                height = Height() - item->NorthSpace() - item->SouthSpace();
            } else if(item->IsValidGap(LayoutItem::kNorthValid)) {
                height = std::min(item->PreferSize().height_, Height() - item->NorthSpace());
                y = Y() + item->NorthSpace();
            } else if(item->IsValidGap(LayoutItem::kSouthValid)) {
                height = std::min(item->PreferSize().height_, Height() - item->SouthSpace());
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