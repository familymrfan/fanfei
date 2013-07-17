#ifndef LINEAR_BOX_LAYOUT_H_
#define LINEAR_BOX_LAYOUT_H_

#include "layout.h"
#include "boxlayout.h"
#include "linear_box_layout_item.h"
#include <vector>
#include <algorithm>
#include <cassert>

namespace ui
{
class LinearBoxLayout:public Layout
{
public:
    LinearBoxLayout() {}

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
        Layout::AddItem(lbli);
    }

    bool InsertItem(uint32_t index, LayoutBaseItem *item) {
        auto box = new BoxLayout;
        box->AddItem(item);
        LinearBoxLayoutItem *lbli = new LinearBoxLayoutItem(box);
        return Layout::InsertItem(index, lbli);
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

    ~LinearBoxLayout() {
        for(uint32_t i = 0;i<layout_items_.size();i++) {
            LayoutBaseItem *bli = layout_items_[i]->GetLayoutBaseItem();
            assert(bli);
            delete bli;
            layout_items_.erase(layout_items_.begin() + i);
        }
    }

protected:
    virtual void Relayout() override {
        BoxToAllocHelper();
        if(IsUnderPrefer()) {
            DoUnderPrefer();
        } else {
            DoExceedPrefer();
        }
        AllocHelperToBox();
    }

    virtual bool IsUnderPrefer() = 0;
    virtual void DoUnderPrefer() = 0;
    virtual void DoExceedPrefer() = 0;
    virtual void AllocHelperToBox() = 0;

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