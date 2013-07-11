#ifndef BOX_LAYOUT_H_
#define BOX_LAYOUT_H_

#include "widget.h"
#include "layout.h"
#include <algorithm>

namespace ui
{
class BoxLayout:public Layout
{
    friend class HBoxLayout;
public:
    virtual Size LimitedMinSize() const override {
        int32_t min_width = 0, width = 0, min_height = 0, height = 0;
        auto iter = layout_items_.begin();
        while(iter != layout_items_.end()) {
            LayoutItem *item = *iter;
            min_width = width;
            if(item->IsValidGap(LayoutItem::kWestValid) && !item->IsValidGap(LayoutItem::kEastValid)) {
                width = item->LimitedMinSize().width_ + item->EastSpace() + item->WestSpace();
            } else if(item->IsValidGap(LayoutItem::kWestValid)){
                width = item->LimitedMinSize().width_ + item->WestSpace();
            } else if(item->IsValidGap(LayoutItem::kEastValid)) {
                width = item->LimitedMinSize().width_ + item->EastSpace();
            } else {
                width = item->LimitedMinSize().width_;
            }

            if(width > min_width) {
                min_width = width;
            }

            min_height = height;
            if(item->IsValidGap(LayoutItem::kNorthValid) && !item->IsValidGap(LayoutItem::kSouthValid)) {
                height = item->LimitedMinSize().height_ + item->NorthSpace() + item->EastSpace();
            } else if(item->IsValidGap(LayoutItem::kNorthValid)){
                height = item->LimitedMinSize().height_ + item->NorthSpace();
            } else if(item->IsValidGap(LayoutItem::kSouthValid)) {
                height = item->LimitedMinSize().height_ + item->SouthSpace();
            } else {
                height = item->LimitedMinSize().height_;
            }

            if(height > min_height) {
                min_height = height;
            }

            iter++;
        }
        return Size(min_width, min_height);
    }

    virtual Size LimitedMaxSize() const override {
        int32_t max_width = 0, width = INT32_MAX, max_height = 0, height = INT32_MAX;
        auto iter = layout_items_.begin();
        while(iter != layout_items_.end()) {
            LayoutItem *item = *iter;
            max_width = width;
            if(item->IsValidGap(LayoutItem::kWestValid) && !item->IsValidGap(LayoutItem::kEastValid)) {
                if(item->LimitedMaxSize().width_ < INT32_MAX - item->EastSpace() - item->WestSpace()) {
                    width = item->LimitedMaxSize().width_ + item->EastSpace() + item->WestSpace();
                }
            } else if(item->IsValidGap(LayoutItem::kWestValid)){
                if(item->LimitedMaxSize().width_ < INT32_MAX - item->WestSpace()) {
                    width = item->LimitedMaxSize().width_ + item->WestSpace();
                }
            } else if(item->IsValidGap(LayoutItem::kEastValid)) {
                if(item->LimitedMaxSize().width_ < INT32_MAX - item->EastSpace()) {
                    width = item->LimitedMaxSize().width_ + item->EastSpace();
                }
            } else {
                width = item->LimitedMaxSize().width_;
            }

            if(width < max_width) {
                max_width = width;
            }

            max_height = height;
            if(item->IsValidGap(LayoutItem::kNorthValid) && !item->IsValidGap(LayoutItem::kSouthValid)) {
                if(item->LimitedMaxSize().height_ < INT32_MAX - item->NorthSpace()) {
                    height = item->LimitedMaxSize().height_ + item->NorthSpace() + item->EastSpace();
                }
            } else if(item->IsValidGap(LayoutItem::kNorthValid)){
                if(item->LimitedMaxSize().height_ < INT32_MAX - item->NorthSpace()) {
                    height = item->LimitedMaxSize().height_ + item->NorthSpace();
                }
            } else if(item->IsValidGap(LayoutItem::kSouthValid)) {
                if(item->LimitedMaxSize().height_ < INT32_MAX - item->SouthSpace()) {
                    height = item->LimitedMaxSize().height_ + item->SouthSpace();
                }
            } else {
                height = item->LimitedMaxSize().height_;
            }

            if(height < max_height) {
                max_height = height;
            }

            iter++;
        }
        return Size(max_width, max_height);
    }

    virtual Size PreferSize() const  override {
        int32_t min_width = 0, width = 0, min_height = 0, height = 0;
        auto iter = layout_items_.begin();
        while(iter != layout_items_.end()) {
            LayoutItem *item = *iter;
            min_width = width;
            if(item->IsValidGap(LayoutItem::kWestValid) && !item->IsValidGap(LayoutItem::kEastValid)) {
                width = item->PreferSize().width_ + item->EastSpace() + item->WestSpace();
            } else if(item->IsValidGap(LayoutItem::kWestValid)){
                width = item->PreferSize().width_ + item->WestSpace();
            } else if(item->IsValidGap(LayoutItem::kEastValid)) {
                width = item->PreferSize().width_ + item->EastSpace();
            } else {
                width = item->PreferSize().width_;
            }

            if(width > min_width) {
                min_width = width;
            }

            min_height = height;
            if(item->IsValidGap(LayoutItem::kNorthValid) && !item->IsValidGap(LayoutItem::kSouthValid)) {
                height = item->PreferSize().height_ + item->NorthSpace() + item->EastSpace();
            } else if(item->IsValidGap(LayoutItem::kNorthValid)){
                height = item->PreferSize().height_ + item->NorthSpace();
            } else if(item->IsValidGap(LayoutItem::kSouthValid)) {
                height = item->PreferSize().height_ + item->SouthSpace();
            } else {
                height = item->PreferSize().height_;
            }

            if(height > min_height) {
                min_height = height;
            }

            iter++;
        }
        return Size(min_width, min_height);
    }
protected:
    virtual void Update() override {
        auto iter = layout_items_.begin();
        while(iter != layout_items_.end()) {
            LayoutItem *item = *iter;
            
            //����
            int32_t width = std::min(item->PreferSize().width_, Width()), height = std::min(item->PreferSize().height_, Height());
            int32_t x = (Width() - width)/2, y = (Height() - height)/2;
            
            if(item->IsValidGap(LayoutItem::kWestValid) && item->IsValidGap(LayoutItem::kEastValid)) {
                x = X() + item->WestSpace();
                width = Width() - item->EastSpace() - item->WestSpace();
            } else if(item->IsValidGap(LayoutItem::kWestValid)){
                    width = std::min(item->PreferSize().width_, Width() - item->WestSpace());
                    x = X() + item->WestSpace();
            } else if(item->IsValidGap(LayoutItem::kEastValid)) {
                    width = std::min(item->PreferSize().width_, Width() - item->EastSpace());
                    x = X() + Width() - item->EastSpace() - width;
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