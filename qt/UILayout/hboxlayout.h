#ifndef HBOXLAYOUT_H_
#define HBOXLAYOUT_H_

#include "layout.h"
#include "boxlayout.h"
#include "linear_box_layout_item.h"
#include <vector>
#include <algorithm>
#include <cassert>

namespace ui
{
class HBoxLayout:public Layout
{
public:
    HBoxLayout() {}

    struct AllocHelper
    {
        enum AllocStatus{
            kNoAlloc = 0,
            kTempAlloc,
            kAlloc
        };

        AllocHelper():
                      section(0),
                      status(kNoAlloc) {
           
        }

        uint32_t section;
        AllocStatus status;
        LinearBoxLayoutItem* box_item;
    };

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
            SetWestSpace(bli->GetLayoutBaseItem(), west_space);
            SetNorthSpace(bli->GetLayoutBaseItem(), north_space);
            SetEastSpace(bli->GetLayoutBaseItem(), east_space);
            SetSouthSpace(bli->GetLayoutBaseItem(), south_space);
    }

    void SetValidGap(LayoutBaseItem *item,
        BoxLayoutItem::GapValid gap_valid, 
        bool valid = true) {
            BoxLayoutItem *bli = GetBoxLayoutItem(item);
            assert(bli);
            bli->SetValidGap(gap_valid, valid);
    }

    void SetStrechFactor(LayoutBaseItem* item, uint32_t strech_factor) {
        LinearBoxLayoutItem *lbli = GetLinearBoxLayoutItem(item);
        assert(lbli);
        lbli->SetStrechFactor(strech_factor);
    }

    void SetStrongElastic(LayoutBaseItem* item, bool strong_elastic) {
        LinearBoxLayoutItem *lbli = GetLinearBoxLayoutItem(item);
        assert(lbli);
        lbli->SetStrongElastic(strong_elastic);
    }

    void AddItem(LayoutBaseItem *item) {
        auto box = new BoxLayout;
        box->AddItem(item);
        LinearBoxLayoutItem *lbli = new LinearBoxLayoutItem(box);
        __super::AddItem(lbli);
    }

    bool InsertItem(uint32_t index, LayoutBaseItem *item) {
        auto box = new BoxLayout;
        box->AddItem(item);
        LinearBoxLayoutItem *lbli = new LinearBoxLayoutItem(box);
        return __super::InsertItem(index, lbli);
    }

    bool RemoveItem(LayoutBaseItem *item) {
        auto iter = layout_items_.begin();
        while (iter != layout_items_.end()) {
            LayoutBaseItem *lbli = (*iter)->GetLayoutBaseItem();
            if(lbli == item) {
                delete lbli;
                layout_items_.erase(iter);
                return true;
            }
            iter++;
        }
        return false;
    }

    bool RemoveItem(uint32_t index) {
        LayoutItem *item = ItemAt(index);
        if(!item) {
            return false;
        }
        delete item;
        layout_items_.erase(layout_items_.begin() + index);
        return true;
    }

    ~HBoxLayout() {
        for(uint32_t i = 0;i<layout_items_.size();i++) {
            LayoutBaseItem *bli = layout_items_[i]->GetLayoutBaseItem();
            assert(bli);
            delete bli;
            layout_items_.erase(layout_items_.begin() + i);
        }
    }

    virtual uint32_t LimitMinWidth() override {
        int width = 0;
        for (LayoutItem* item:layout_items_) {
             LayoutBaseItem *base_item = item->GetLayoutBaseItem();
             assert(base_item);
             width += base_item->LimitMinWidth();
        }
        return width;
    }

    virtual uint32_t LimitMinHeight() override {
        uint32_t height = 0;
        for (LayoutItem* item:layout_items_) {
            LayoutBaseItem *base_item = item->GetLayoutBaseItem();
            assert(base_item);
            if(base_item->LimitMinHeight() > height) {
                height = base_item->LimitMinHeight();
            }
        }
        return height;
    }

    virtual uint32_t LimitMaxWidth() override {
        uint32_t width = MAX_LENGTH;
        for (LayoutItem* item:layout_items_) {
            LayoutBaseItem *base_item = item->GetLayoutBaseItem();
            if(width < MAX_LENGTH - base_item->LimitMaxWidth()) {
                width += base_item->LimitMaxWidth();
            }
        }
        return width;
    }

    virtual uint32_t LimitMaxHeight() override {
        uint32_t height = MAX_LENGTH;
        for (LayoutItem* item:layout_items_) {
            LayoutBaseItem *base_item = item->GetLayoutBaseItem();
            if(base_item->LimitMaxHeight() < height) {
                height = base_item->LimitMaxHeight();
            }
        }

        return height;
    }

    virtual uint32_t PreferWidth() override {
        uint32_t width = 0;
        for (LayoutItem* item:layout_items_) {
            LayoutBaseItem *base_item = item->GetLayoutBaseItem();
            width += std::max(base_item->LimitMinWidth(), base_item->PreferWidth());
        }
        return width;
    }

    virtual uint32_t PreferHeight() override {
        uint32_t height = 0, hign_height = 0;
        for (LayoutItem* item:layout_items_) {
            LayoutBaseItem *base_item = item->GetLayoutBaseItem();
            hign_height = std::max(base_item->LimitMinHeight(), base_item->PreferHeight());
            if(hign_height > height) {
                height = hign_height;
            }
        }
        return height;
    }

protected:
    virtual void Relayout() override {
        BoxToAllocHelper();
        uint32_t alloc_size = Width();
        if(alloc_size < PreferWidth()) {
            DoUnderPrefer();
        } else {
            DoExceedPrefer();
        }
        AllocHelperToBox();
    }

    void BoxToAllocHelper() {
        alloc_sections_.clear();
        auto iter = layout_items_.begin();
        while(iter != layout_items_.end()) {
            AllocHelper helper;
            helper.box_item = reinterpret_cast<LinearBoxLayoutItem *>(*iter);
            alloc_sections_.push_back(helper);
            iter++;
        }
    }

    void DoUnderPrefer() {
        int32_t alloc_size = Width();
        int32_t sum_factor = 0;

        auto iter = alloc_sections_.begin();
        while(iter != alloc_sections_.end()) {
            LayoutBaseItem* box = iter->box_item->GetLayoutBaseItem();
            assert(box);
            if(box->LimitMinWidth() > box->PreferWidth()) {
                iter->section = box->LimitMinWidth();
                iter->status = AllocHelper::kAlloc;
                alloc_size -= iter->section;
            } else {
                sum_factor += box->PreferWidth();
            }
            iter++;
        }

        iter = alloc_sections_.begin();
        while(iter != alloc_sections_.end()) {
            LayoutBaseItem* box = iter->box_item->GetLayoutBaseItem();
            assert(box);
            if(iter->status == AllocHelper::kNoAlloc) {
                iter->section = (uint32_t)((float)alloc_size/sum_factor*box->PreferWidth());
            }
            iter++;
        }
    }

    void DoExceedPrefer() {
        int32_t alloc_size = Width();
        int32_t sum_factor = 0;

        bool strong = IsStrongWeakAllInNoAlloc();

        auto iter = alloc_sections_.begin();
        while(iter != alloc_sections_.end()) {
            LayoutBaseItem* box = iter->box_item->GetLayoutBaseItem();
            assert(box);

            if(iter->box_item->StrechFactor() == 0 || strong && !iter->box_item->IsStrongElastic()) {
                iter->section = std::max(box->LimitMinWidth(), box->PreferWidth());
                iter->status = AllocHelper::kAlloc;
                alloc_size -= iter->section;
            } else {
                sum_factor += iter->box_item->StrechFactor();
            }
            iter++;
        }
        AllocSectionByStrechFactor(alloc_size, sum_factor);
    }

    void AllocSectionByStrechFactor(int32_t alloc_size, int32_t sum_factor) {
        auto first = alloc_sections_.begin();
        while(first != alloc_sections_.end()) {
            if(first->status == AllocHelper::kNoAlloc) {
                break;
            }
            first++;
        }

        if(first != alloc_sections_.end()) {
            bool alloc = false;
            if(first->status == AllocHelper::kNoAlloc) {
                LayoutBaseItem* box = first->box_item->GetLayoutBaseItem();
                first->section = (uint32_t)((float)alloc_size/sum_factor*first->box_item->StrechFactor());
                if(first->section < box->LimitMinWidth()) {
                    first->section = box->LimitMinWidth();
                    alloc = true;
                } else if (first->section > box->LimitMaxWidth()) {
                    first->section = box->LimitMaxWidth();
                    alloc = true;
                } else if(first->section < box->PreferWidth()){
                    first->section = box->PreferWidth();
                    alloc = true;
                } else {
                    first->status = AllocHelper::kTempAlloc;
                    alloc = false;
                }

                if(alloc) {
                    first->status = AllocHelper::kAlloc;
                    ResetTempAllocToNoAlloc();

                    alloc_size = Width();
                    sum_factor = 0;

                    auto iter = alloc_sections_.begin();
                    while(iter != alloc_sections_.end()) {
                        if(iter->status != AllocHelper::kNoAlloc) {
                            alloc_size -= iter->section;
                        } else {
                            sum_factor += iter->box_item->StrechFactor();
                        }
                        iter++;
                    }
                } else {
                    alloc_size -= first->section;
                    sum_factor -= first->box_item->StrechFactor();
                }
                
                AllocSectionByStrechFactor(alloc_size, sum_factor);
            }
        }
    }

    bool IsStrongWeakAllInNoAlloc() {
        bool has_strong = false;
        bool has_weak   = false;

        auto iter = alloc_sections_.begin();
        while(iter != alloc_sections_.end()) {
            AllocHelper helper = *iter;
            if(helper.status == AllocHelper::kNoAlloc) {
                if(helper.box_item->IsStrongElastic()) {
                    has_strong = true;
                } else {
                    has_weak = true;
                }
            } 
            iter++;
        }

        if(has_strong && has_weak) {
            return true;
        }

        return false;
    }

    void ResetTempAllocToNoAlloc() {
        auto iter = alloc_sections_.begin();
        while(iter != alloc_sections_.end()) {
            if(iter->status == AllocHelper::kTempAlloc) {
                iter->status = AllocHelper::kNoAlloc;
            }
            iter++;
        }
    }

    void AllocHelperToBox() {
        auto iter = alloc_sections_.begin();
        int32_t pre_x = X();
        while(iter != alloc_sections_.end()) {
            iter->box_item->SetGeometry(pre_x, Y(), iter->section, Height());
            iter->box_item->Relayout();
            pre_x += iter->section;
            iter++;
        }
    }

    LinearBoxLayoutItem* GetLinearBoxLayoutItem(LayoutBaseItem *item) {
        auto iter = layout_items_.begin();
        while (iter != layout_items_.end()) {
            BoxLayout *bli = reinterpret_cast<BoxLayout*>((*iter)->GetLayoutBaseItem());
            assert(bli);
            assert(bli->ItemAt(0));
            if(bli->ItemAt(0)->GetLayoutBaseItem() == item) {
                return reinterpret_cast<LinearBoxLayoutItem*>(*iter);
            }
            iter++;
        }
        return nullptr;
    }

    BoxLayoutItem* GetBoxLayoutItem(LayoutBaseItem *item) {
        auto iter = layout_items_.begin();
        while (iter != layout_items_.end()) {
            BoxLayout *bli = reinterpret_cast<BoxLayout*>((*iter)->GetLayoutBaseItem());
            assert(bli);
            assert(bli->ItemAt(0));
            if(bli->ItemAt(0)->GetLayoutBaseItem() == item) {
                return reinterpret_cast<BoxLayoutItem*>(bli->ItemAt(0));
            }
            iter++;
        }
        return nullptr;
    }

    std::vector<AllocHelper> alloc_sections_;
};
} // namespace ui

#endif