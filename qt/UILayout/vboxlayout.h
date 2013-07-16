#ifndef VBOXLAYOUT_H_
#define VBOXLAYOUT_H_

#include "layout.h"
#include "boxlayout.h"
#include "linear_box_layout.h"
#include <vector>
#include <algorithm>
#include <cassert>

namespace ui
{
class VBoxLayout:public LinearBoxLayout
{
public:
    VBoxLayout() {}

protected:
    void CalculateLimitMinWidth() {
        uint32_t width = 0;
        for (LayoutItem* item:layout_items_) {
            LayoutBaseItem *base_item = item->GetLayoutBaseItem();
            assert(base_item);
            if(base_item->LimitMinWidth() > width) {
                width = base_item->LimitMinWidth();
            }
        }
        SetLimitMinWidth(width);
    }

    void CalculateLimitMinHeight() {
        int height = 0;
        for (LayoutItem* item:layout_items_) {
            LayoutBaseItem *base_item = item->GetLayoutBaseItem();
            assert(base_item);
            height += base_item->LimitMinHeight();
        }
        SetLimitMinHeight(height);
    }

    void CalculateLimitMaxWidth() {
        uint32_t width = MAX_LENGTH;
        for (LayoutItem* item:layout_items_) {
            LayoutBaseItem *base_item = item->GetLayoutBaseItem();
            if(base_item->LimitMaxWidth() < width) {
                width = base_item->LimitMaxWidth();
            }
        }
        SetLimitMaxWidth(width);
    }

    void CalculateLimitMaxHeight() {
        uint32_t height = MAX_LENGTH;
        for (LayoutItem* item:layout_items_) {
            LayoutBaseItem *base_item = item->GetLayoutBaseItem();
            if(height < MAX_LENGTH - base_item->LimitMaxHeight()) {
                height += base_item->LimitMaxHeight();
            }
        }
        SetLimitMaxHeight(height);
    }

    void CalculatePreferWidth() {
        uint32_t width = 0, hign_width = 0;
        for (LayoutItem* item:layout_items_) {
            LayoutBaseItem *base_item = item->GetLayoutBaseItem();
            hign_width = std::max(base_item->LimitMinWidth(), base_item->PreferWidth());
            if(hign_width > width) {
                width = hign_width;
            }
        }
        SetPreferWidth(width);
    }

    void CalculatePreferHeight() {
        uint32_t height = 0;
        for (LayoutItem* item:layout_items_) {
            LayoutBaseItem *base_item = item->GetLayoutBaseItem();
            height += std::max(base_item->LimitMinHeight(), base_item->PreferHeight());
        }
        SetPreferHeight(height);
    }

    void CalculateItemsSize() {
        CalculateLimitMinWidth();
        CalculateLimitMinHeight();
        CalculateLimitMaxWidth();
        CalculateLimitMaxHeight();
        CalculatePreferWidth();
        CalculatePreferHeight();
    }

    virtual void Relayout() override {
        CalculateItemsSize();
        Layout::Relayout();
    }

    virtual bool IsUnderPrefer() override {
        return Height() < PreferHeight();
    }

    virtual void DoUnderPrefer() override {
        int32_t alloc_size = Height();
        int32_t sum_factor = 0;

        auto iter = alloc_sections_.begin();
        while(iter != alloc_sections_.end()) {
            LayoutBaseItem* box = iter->box_item->GetLayoutBaseItem();
            assert(box);
            if(box->LimitMinHeight() > box->PreferHeight()) {
                iter->section = box->LimitMinHeight();
                iter->status = AllocHelper::kAlloc;
                alloc_size -= iter->section;
            } else {
                sum_factor += box->PreferHeight();
            }
            iter++;
        }

        iter = alloc_sections_.begin();
        while(iter != alloc_sections_.end()) {
            LayoutBaseItem* box = iter->box_item->GetLayoutBaseItem();
            assert(box);
            if(iter->status == AllocHelper::kNoAlloc) {
                iter->section = (uint32_t)((float)alloc_size/sum_factor*box->PreferHeight());
            }
            iter++;
        }
    }

    virtual void DoExceedPrefer() override {
        int32_t alloc_size = Height();
        int32_t sum_factor = 0;

        bool strong = IsStrongWeakAllInNoAlloc();

        auto iter = alloc_sections_.begin();
        while(iter != alloc_sections_.end()) {
            LayoutBaseItem* box = iter->box_item->GetLayoutBaseItem();
            assert(box);

            if(iter->box_item->StrechFactor() == 0 || (strong && !iter->box_item->IsStrongElastic())) {
                iter->section = std::max(box->LimitMinHeight(), box->PreferHeight());
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
        int32_t pre_y = Y();
        while(iter != alloc_sections_.end()) {
            iter->box_item->SetGeometry(X(), pre_y, Width(),iter->section);
            iter->box_item->Relayout();
            pre_y += iter->section;
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
                if(first->section < box->LimitMinHeight()) {
                    first->section = box->LimitMinHeight();
                    alloc = true;
                } else if (first->section > box->LimitMaxHeight()) {
                    first->section = box->LimitMaxHeight();
                    alloc = true;
                } else if(first->section < box->PreferHeight()){
                    first->section = box->PreferHeight();
                    alloc = true;
                } else {
                    first->status = AllocHelper::kTempAlloc;
                    alloc = false;
                }

                if(alloc) {
                    first->status = AllocHelper::kAlloc;
                    ResetTempAllocToNoAlloc();

                    alloc_size = Height();
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