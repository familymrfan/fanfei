#ifndef HBOXLAYOUT_H_
#define HBOXLAYOUT_H_

#include "layout.h"
#include "boxlayout.h"
#include "linear_box_layout.h"
#include <vector>
#include <algorithm>
#include <cassert>

namespace ui
{
class HBoxLayout:public LinearBoxLayout
{
public:
    HBoxLayout() {}

protected:
    virtual uint32_t CalculateLimitMinWidth() override {
        int width = 0;
        for (LayoutItem* item:layout_items_) {
            LayoutBaseItem *base_item = item->GetLayoutBaseItem();
            assert(base_item);
            width += base_item->LimitMinWidth();
        }
        
        return width;
    }

    virtual uint32_t CalculateLimitMinHeight() override {
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

    virtual uint32_t CalculateLimitMaxWidth() override {
        uint32_t width = MAX_LENGTH;
        for (LayoutItem* item:layout_items_) {
            LayoutBaseItem *base_item = item->GetLayoutBaseItem();
            if(width < MAX_LENGTH - base_item->LimitMaxWidth()) {
                width += base_item->LimitMaxWidth();
            }
        }
        
        return width;
    }

    virtual uint32_t CalculateLimitMaxHeight() override {
        uint32_t height = MAX_LENGTH;
        for (LayoutItem* item:layout_items_) {
            LayoutBaseItem *base_item = item->GetLayoutBaseItem();
            if(base_item->LimitMaxHeight() < height) {
                height = base_item->LimitMaxHeight();
            }
        }
        
        return height;
    }

    virtual uint32_t CalculatePreferWidth() override {
        uint32_t width = 0;
        for (LayoutItem* item:layout_items_) {
            LayoutBaseItem *base_item = item->GetLayoutBaseItem();
            width += std::max(base_item->LimitMinWidth(), base_item->PreferWidth());
        }
        
        return width;
    }

    virtual uint32_t CalculatePreferHeight() override {
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

    virtual bool IsUnderPrefer() override {
        return Width() < PreferWidth();
    }

    virtual void DoUnderPrefer() override {
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

    virtual void DoExceedPrefer() override {
        int32_t alloc_size = Width();
        int32_t sum_factor = 0;

        bool strong = IsStrongWeakAllInNoAlloc();

        auto iter = alloc_sections_.begin();
        while(iter != alloc_sections_.end()) {
            LayoutBaseItem* box = iter->box_item->GetLayoutBaseItem();
            assert(box);

            if(iter->box_item->StrechFactor() == 0 || (strong && !iter->box_item->IsStrongElastic())) {
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

    virtual void AllocHelperToBox() override {
        auto iter = alloc_sections_.begin();
        int32_t pre_x = X();
        while(iter != alloc_sections_.end()) {
            iter->box_item->SetGeometry(pre_x, Y(), iter->section, Height());
            iter->box_item->Relayout();
            pre_x += iter->section;
            iter++;
        }
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
};
} // namespace ui

#endif