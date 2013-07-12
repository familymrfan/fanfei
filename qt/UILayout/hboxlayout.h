#ifndef HBOXLAYOUT_H_
#define HBOXLAYOUT_H_

#include "layout.h"
#include "boxlayout.h"
#include <vector>
#include <algorithm>
#include <cassert>

namespace ui
{
class HBoxLayout:public Layout
{
public:
    HBoxLayout():recal_limit_size_(true) {}

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

        int32_t section;
        AllocStatus status;
        BoxLayout* box;
    };


    virtual void AddItem(LayoutItem *item) override {
        auto box = new BoxLayout;
        box->AddItem(item);
        boxes_.push_back(box);
        SetReCalLimitSize();
    }

    virtual bool InsertItem(int32_t index, LayoutItem *item) {
        auto box = new BoxLayout;
        box->AddItem(item);
        if(index < 0 || index > boxes_.size())
            return false;
        boxes_.insert(boxes_.begin()+index, box);
        SetReCalLimitSize();
        return true;
    }

    virtual void RemoveItem(LayoutItem *item) {
        for(size_t i = 0;i<boxes_.size();i++) {
            if(item == ItemAt(i)) {
                delete boxes_[i];
                boxes_.erase(boxes_.begin() + i);
                break;
            }
        }
    }

    virtual LayoutItem* ItemAt(int32_t index) {
        if(index < 0 || index > boxes_.size()) {
            return nullptr;
        }
        return boxes_[index]->ItemAt(0);
    }

    ~HBoxLayout() {
        for(size_t i = 0;i<boxes_.size();i++) {
            delete boxes_[i];
            boxes_.erase(boxes_.begin() + i);
        }
    }

    virtual Size LimitedMinSize() override {
        if(!recal_limit_size_) {
            //return limited_min_size_;
        }
        recal_limit_size_ = false;

        int width = 0, height = 0;
        for (BoxLayout* box:boxes_) {
             width += box->LimitedMinSize().width_;
             if(box->LimitedMinSize().height_ > height) {
                 height = box->LimitedMinSize().height_;
             }
        }
        limited_min_size_ = Size(width, height);
        return limited_min_size_;
    }

    virtual Size LimitedMaxSize() override {
        if(!recal_limit_size_) {
            //return limited_max_size_;
        }
        recal_limit_size_ = false;

        int width = INT32_MAX, height = INT32_MAX;
        for (BoxLayout* box:boxes_) {
            if(width < INT32_MAX - box->LimitedMaxSize().width_) {
                width += box->LimitedMaxSize().width_;
            }
            if(box->LimitedMaxSize().height_ < height) {
                height = box->LimitedMaxSize().height_;
            }
        }

        limited_max_size_ = Size(width, height);
        return limited_max_size_;
    }

    virtual Size PreferSize() override {
        if(!recal_limit_size_) {
            //return prefer_size_;
        }
        recal_limit_size_ = false;

        int width = 0, height = 0;
        for (BoxLayout* box:boxes_) {
            width += std::max(box->PreferSize().width_, box->LimitedMinSize().width_);
            if(int32_t hign_height = std::max(box->PreferSize().height_, box->LimitedMinSize().height_) > height) {
                height = hign_height;
            }
        }

        prefer_size_ = Size(width, height);
        return prefer_size_;
    }

    void SetReCalLimitSize() {
        recal_limit_size_ = true;
    }
protected:
    virtual void Update() override {
        BoxToAllocHelper();
        int32_t alloc_size = Width();
        if(alloc_size < PreferSize().width_) {
            DoUnderPrefer();
        } else {
            DoExceedPrefer();
        }
        AllocHelperToBox();
    }

    void BoxToAllocHelper() {
        alloc_sections_.clear();
        auto iter = boxes_.begin();
        while(iter != boxes_.end()) {
            AllocHelper helper;
            helper.box = *iter;
            alloc_sections_.push_back(helper);
            iter++;
        }
    }

    void DoUnderPrefer() {
        int32_t alloc_size = Width();
        int32_t sum_factor = 0;

        auto iter = alloc_sections_.begin();
        while(iter != alloc_sections_.end()) {
            if(iter->box->LimitedMinSize().width_ > iter->box->PreferSize().width_) {
                iter->section = iter->box->LimitedMinSize().width_;
                iter->status = AllocHelper::kAlloc;
                alloc_size -= iter->section;
            } else {
                sum_factor += iter->box->PreferSize().width_;
            }
            iter++;
        }

        iter = alloc_sections_.begin();
        while(iter != alloc_sections_.end()) {
            if(iter->status == AllocHelper::kNoAlloc) {
                iter->section = (int32_t)((float)alloc_size/sum_factor*iter->box->PreferSize().width_);
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
            LayoutItem* item = iter->box->ItemAt(0);
            assert(item);

            if(item->StrechFactor() == 0 || strong && !item->IsStrongElastic()) {
                iter->section = std::max(iter->box->LimitedMinSize().width_, iter->box->PreferSize().width_);
                alloc_size -= iter->section;
            } else {
                sum_factor += item->StrechFactor();
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
                first->section = (int32_t)((float)alloc_size/sum_factor*first->box->ItemAt(0)->StrechFactor());
                if(first->box->LessThanLimitMinWidth(first->section)) {
                    first->section = first->box->LimitedMinSize().width_;
                    alloc = true;
                } else if (first->box->MoreThanLimitMaxWidth(first->section)) {
                    first->section = first->box->LimitedMaxSize().width_;
                    alloc = true;
                } else if(first->box->LessThanPreferWidth(first->section)){
                    first->section = first->box->PreferSize().width_;
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
                        LayoutItem* item = iter->box->ItemAt(0);
                        assert(item);
                        if(iter->status != AllocHelper::kNoAlloc) {
                            alloc_size -= iter->section;
                        } else {
                            sum_factor += item->StrechFactor();
                        }
                        iter++;
                    }
                } else {
                    alloc_size -= first->section;
                    sum_factor -= first->box->ItemAt(0)->StrechFactor();
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
                if(helper.box->IsStrongElastic()) {
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
            iter->box->SetGeometry(pre_x, Y(), iter->section, Height());
            iter->box->Update();
            pre_x += iter->section;
            iter++;
        }
    }

    std::vector<BoxLayout*> boxes_;
    std::vector<AllocHelper> alloc_sections_;
    bool recal_limit_size_;
};
} // namespace ui

#endif