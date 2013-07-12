#ifndef BOX_LAYOUT_H_
#define BOX_LAYOUT_H_

#include "widget.h"
#include "layout.h"
#include "box_layout_item.h"
#include <algorithm>
#include <cassert>

namespace ui
{
class BoxLayout:public Layout
{
public:
    BoxLayout() {}

    void SetWestSpace(LayoutBaseItem *item, uint32_t west_space) {
        BoxLayoutItem *bli = GetBoxLayoutItem(item);
        assert(bli);
        bli->SetWestSpace(west_space);
    }

    void SetNorthSpace(LayoutBaseItem *item, uint32_t north_space) {
        BoxLayoutItem *bli = GetBoxLayoutItem(item);
        assert(bli);
        bli->SetNorthSpace(north_space);
    }

    void SetEastSpace(LayoutBaseItem *item, uint32_t east_space) {
        BoxLayoutItem *bli = GetBoxLayoutItem(item);
        assert(bli);
        bli->SetEastSpace(east_space);
    }

    void SetSouthSpace(LayoutBaseItem *item, uint32_t south_space) {
        BoxLayoutItem *bli = GetBoxLayoutItem(item);
        assert(bli);
        bli->SetSouthSpace(south_space);
    }

    void SetAround(LayoutBaseItem *item, 
                   uint32_t west_space, 
                   uint32_t north_space, 
                   uint32_t east_space, 
                   uint32_t south_space) {
        BoxLayoutItem *bli = GetBoxLayoutItem(item);
        assert(bli);
        BoxLayout::SetWestSpace(bli->GetLayoutBaseItem(), west_space);
        BoxLayout::SetNorthSpace(bli->GetLayoutBaseItem(), north_space);
        BoxLayout::SetEastSpace(bli->GetLayoutBaseItem(), east_space);
        BoxLayout::SetSouthSpace(bli->GetLayoutBaseItem(), south_space);
    }

    void SetValidGap(LayoutBaseItem *item,
                     BoxLayoutItem::GapValid gap_valid, 
                     bool valid = true) {
        BoxLayoutItem *bli = GetBoxLayoutItem(item);
        assert(bli);
        bli->SetValidGap(gap_valid, valid);
    }

    void AddItem(LayoutBaseItem *item){
        BoxLayoutItem *bli = new BoxLayoutItem(item);
        __super::AddItem(bli);
    }

    bool InsertItem(int32_t index, LayoutBaseItem *item){
        BoxLayoutItem *bli = new BoxLayoutItem(item);
        return __super::InsertItem(index, bli);
    }

    bool RemoveItem(LayoutBaseItem *item) {
        auto iter = layout_items_.begin();
        while (iter != layout_items_.end()) {
            LayoutBaseItem *bli = (*iter)->GetLayoutBaseItem();
            if(bli == item) {
                delete bli;
                layout_items_.erase(iter);
                return true;
            }
            iter++;
        }
        return false;
    }

    bool RemoveItem(uint32_t index) {
        LayoutItem *bli = ItemAt(index);
        if(!bli) {
            return false;
        }
        delete bli;
        layout_items_.erase(layout_items_.begin() + index);
        return true;
    }

    virtual uint32_t LimitMinWidth() override {
        int32_t min_width = 0, width = 0;
        auto iter = layout_items_.begin();
        while(iter != layout_items_.end()) {
            BoxLayoutItem *item = reinterpret_cast<BoxLayoutItem*>(*iter);
            LayoutBaseItem *BaseItem = item->GetLayoutBaseItem();
            min_width = width;
            if(item->IsValidGap(BoxLayoutItem::kWestValid) && !item->IsValidGap(BoxLayoutItem::kEastValid)) {
                width = BaseItem->LimitMinWidth() + item->WestSpace() + item->EastSpace();
            } else if(item->IsValidGap(BoxLayoutItem::kWestValid)){
                width = BaseItem->LimitMinWidth() + item->WestSpace();
            } else if(item->IsValidGap(BoxLayoutItem::kEastValid)) {
                width = BaseItem->LimitMinWidth() + item->EastSpace();
            } else {
                width = BaseItem->LimitMinWidth();
            }

            if(width > min_width) {
                min_width = width;
            }
            iter++;
        }
        return min_width;
    }

    virtual uint32_t LimitMinHeight() override {
        int32_t min_height = 0, height = 0;
        auto iter = layout_items_.begin();
        while(iter != layout_items_.end()) {
            BoxLayoutItem *item = reinterpret_cast<BoxLayoutItem*>(*iter);
            LayoutBaseItem *BaseItem = item->GetLayoutBaseItem();
            min_height = height;
            if(item->IsValidGap(BoxLayoutItem::kNorthValid) && !item->IsValidGap(BoxLayoutItem::kSouthValid)) {
                height = BaseItem->LimitMinHeight() + item->NorthSpace() + item->SouthSpace();
            } else if(item->IsValidGap(BoxLayoutItem::kNorthValid)){
                height = BaseItem->LimitMinHeight() + item->NorthSpace();
            } else if(item->IsValidGap(BoxLayoutItem::kSouthValid)) {
                height = BaseItem->LimitMinHeight() + item->SouthSpace();
            } else {
                height = BaseItem->LimitMinHeight();
            }

            if(height > min_height) {
                min_height = height;
            }
            iter++;
        }
        return min_height;
    }

    virtual uint32_t LimitMaxWidth() override {
        int32_t max_width = 0, width = MAX_LENGTH;
        auto iter = layout_items_.begin();
        while(iter != layout_items_.end()) {
            BoxLayoutItem *item = reinterpret_cast<BoxLayoutItem*>(*iter);
            LayoutBaseItem *BaseItem = item->GetLayoutBaseItem();
            max_width = width;
            if(item->IsValidGap(BoxLayoutItem::kWestValid) && !item->IsValidGap(BoxLayoutItem::kEastValid)) {
                if(BaseItem->LimitMaxWidth() < MAX_LENGTH - item->EastSpace() - item->WestSpace()) {
                    width = BaseItem->LimitMaxWidth() + item->EastSpace() + item->WestSpace();
                }
            } else if(item->IsValidGap(BoxLayoutItem::kWestValid)){
                if(BaseItem->LimitMaxWidth() < MAX_LENGTH - item->WestSpace()) {
                    width = BaseItem->LimitMaxWidth() + item->WestSpace();
                }
            } else if(item->IsValidGap(BoxLayoutItem::kEastValid)) {
                if(BaseItem->LimitMaxWidth() < MAX_LENGTH - item->EastSpace()) {
                    width = BaseItem->LimitMaxWidth() + item->EastSpace();
                }
            } else {
                width = BaseItem->LimitMaxWidth();
            }

            if(width < max_width) {
                max_width = width;
            }

            iter++;
        }
        return max_width;
    }

    virtual uint32_t LimitMaxHeight() override {
        int32_t max_height = 0, height = MAX_LENGTH;
        auto iter = layout_items_.begin();
        while(iter != layout_items_.end()) {
            BoxLayoutItem *item = reinterpret_cast<BoxLayoutItem*>(*iter);
            LayoutBaseItem *BaseItem = item->GetLayoutBaseItem();
            max_height = height;
            if(item->IsValidGap(BoxLayoutItem::kNorthValid) && !item->IsValidGap(BoxLayoutItem::kSouthValid)) {
                if(BaseItem->LimitMaxHeight() < MAX_LENGTH - item->NorthSpace() - item->SouthSpace()) {
                    height = BaseItem->LimitMaxHeight() + item->NorthSpace() + item->SouthSpace();
                }
            } else if(item->IsValidGap(BoxLayoutItem::kNorthValid)){
                if(BaseItem->LimitMaxHeight() < MAX_LENGTH - item->NorthSpace()) {
                    height = BaseItem->LimitMaxHeight() + item->NorthSpace();
                }
            } else if(item->IsValidGap(BoxLayoutItem::kSouthValid)) {
                if(BaseItem->LimitMaxHeight() < MAX_LENGTH - item->SouthSpace()) {
                    height = BaseItem->LimitMaxHeight() + item->SouthSpace();
                }
            } else {
                height = BaseItem->LimitMaxHeight();
            }

            if(height < max_height) {
                max_height = height;
            }

            iter++;
        }
        return max_height;
    }

    virtual uint32_t PreferWidth() override {
        int32_t prefer_width = 0, width = 0;
        auto iter = layout_items_.begin();
        while(iter != layout_items_.end()) {
            BoxLayoutItem *item = reinterpret_cast<BoxLayoutItem*>(*iter);
            LayoutBaseItem *BaseItem = item->GetLayoutBaseItem();
            prefer_width = width;
            if(item->IsValidGap(BoxLayoutItem::kWestValid) && !item->IsValidGap(BoxLayoutItem::kEastValid)) {
                if(BaseItem->PreferWidth() < MAX_LENGTH - item->EastSpace() - item->WestSpace()) {
                    width = BaseItem->PreferWidth() + item->EastSpace() + item->WestSpace();
                }
            } else if(item->IsValidGap(BoxLayoutItem::kWestValid)){
                if(BaseItem->PreferWidth() < MAX_LENGTH - item->WestSpace()) {
                    width = BaseItem->PreferWidth() + item->WestSpace();
                }
            } else if(item->IsValidGap(BoxLayoutItem::kEastValid)) {
                if(BaseItem->PreferWidth() < MAX_LENGTH - item->EastSpace()) {
                    width = BaseItem->PreferWidth() + item->EastSpace();
                }
            } else {
                width = BaseItem->PreferWidth();
            }

            if(width > prefer_width) {
                prefer_width = width;
            }
            iter++;
        }
        return prefer_width;
    }


    virtual uint32_t PreferHeight() override {
        int32_t prefer_height = 0, height = 0;
        auto iter = layout_items_.begin();
        while(iter != layout_items_.end()) {
            BoxLayoutItem *item = reinterpret_cast<BoxLayoutItem*>(*iter);
            LayoutBaseItem *BaseItem = item->GetLayoutBaseItem();
            prefer_height = height;
            if(item->IsValidGap(BoxLayoutItem::kNorthValid) && !item->IsValidGap(BoxLayoutItem::kSouthValid)) {
                if(BaseItem->PreferHeight() < MAX_LENGTH - item->NorthSpace() - item->EastSpace()) {
                    height = BaseItem->PreferHeight() + item->NorthSpace() + item->EastSpace();
                }
            } else if(item->IsValidGap(BoxLayoutItem::kNorthValid)){
                if(BaseItem->PreferHeight() < MAX_LENGTH - item->NorthSpace()) {
                    height = BaseItem->PreferHeight() + item->NorthSpace();
                }
            } else if(item->IsValidGap(BoxLayoutItem::kSouthValid)) {
                if(BaseItem->PreferHeight() < MAX_LENGTH - item->SouthSpace()) {
                    height = BaseItem->PreferHeight() + item->SouthSpace();
                }
            } else {
                height = BaseItem->PreferHeight();
            }

            if(height > prefer_height) {
                prefer_height = height;
            }

            iter++;
        }
        return prefer_height;
    }

protected:
    virtual void Relayout() override {
        auto iter = layout_items_.begin();
        while(iter != layout_items_.end()) {
            BoxLayoutItem *item = reinterpret_cast<BoxLayoutItem*>(*iter);
            LayoutBaseItem *BaseItem = item->GetLayoutBaseItem();

            int32_t width = std::min(BaseItem->PreferWidth(), Width()), height = std::min(BaseItem->PreferHeight(), Height());
            int32_t x = X() + (Width() - width)/2, y = Y() + (Height() - height)/2;
            
            if(item->IsValidGap(BoxLayoutItem::kWestValid) && item->IsValidGap(BoxLayoutItem::kEastValid)) {
                x = X() + item->WestSpace();
                width = Width() - item->EastSpace() - item->WestSpace();
            } else if(item->IsValidGap(BoxLayoutItem::kWestValid)){
                width = std::min(BaseItem->PreferWidth(), Width() - item->WestSpace());
                x = X() + item->WestSpace();
            } else if(item->IsValidGap(BoxLayoutItem::kEastValid)) {
                width = std::min(BaseItem->PreferWidth(), Width() - item->EastSpace());
                x = X() + Width() - item->EastSpace() - width;
            }

            width = std::max(0, width);

            if(item->IsValidGap(BoxLayoutItem::kNorthValid) && item->IsValidGap(BoxLayoutItem::kSouthValid)) {
                y = Y() + item->NorthSpace();
                height = Height() - item->NorthSpace() - item->SouthSpace();
            } else if(item->IsValidGap(BoxLayoutItem::kNorthValid)) {
                height = std::min(BaseItem->PreferHeight(), Height() - item->NorthSpace());
                y = Y() + item->NorthSpace();
            } else if(item->IsValidGap(BoxLayoutItem::kSouthValid)) {
                height = std::min(BaseItem->PreferHeight(), Height() - item->SouthSpace());
                y = Y() + Height() - item->SouthSpace() - height;
            }

            height = std::max(0, height);

            item->SetGeometry(x, y, width, height);
            item->Relayout();
            iter++;
        }
    }

    BoxLayoutItem* GetBoxLayoutItem(LayoutBaseItem *item) {
        auto iter = layout_items_.begin();
        while (iter != layout_items_.end()) {
            LayoutBaseItem *bli = (*iter)->GetLayoutBaseItem();
            if(bli == item) {
                return reinterpret_cast<BoxLayoutItem*>(*iter);
            }
            iter++;
        }
        return nullptr;
    }
};

} // namespace ui

#endif // BOX_LATOUT_H_