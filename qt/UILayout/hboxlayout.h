#ifndef HBOXLAYOUT_H_
#define HBOXLAYOUT_H_

#include "layout.h"
#include "boxlayout.h"
#include <vector>

namespace ui
{
class HBoxLayout:public Layout
{
public:
    virtual void AddItem(LayoutItem *item) override {
        auto box = new BoxLayout;
        box->AddItem(item);
        boxes_.push_back(box);
    }

    virtual LayoutItem* ItemAt(int32_t index) {
        if(index < 0 || index > boxes_.size()) {
            return nullptr;
        }
        return boxes_[index]->ItemAt(0);
    }

    ~HBoxLayout() {
        //TODO(fanfei):clear boxes
    }

    virtual Size LimitedMinSize() const override {
        int width = 0, height = 0;
        for (BoxLayout* box:boxes_) {
             width += box->LimitedMinSize().width_;
             if(box->LimitedMinSize().height_ > height) {
                 height = box->LimitedMinSize().height_;
             }
        }
        return Size(width, height);
    }

    virtual Size LimitedMaxSize() const override {
        int width = 0, height = INT32_MAX;
        for (BoxLayout* box:boxes_) {
            width += box->LimitedMaxSize().width_;
            if(box->LimitedMaxSize().height_ < height) {
                height = box->LimitedMaxSize().height_;
            }
        }
        return Size(width, height);
    }

    virtual Size PreferSize() const override {
        int width = 0, height = 0;
        for (BoxLayout* box:boxes_) {
            width += box->PreferSize().width_;
            if(box->PreferSize().height_ > height) {
                height = box->PreferSize().height_;
            }
        }
        return Size(width, height);
    }

protected:
    virtual void Update() override {
        ReachPrefer();


    }

    void ReachPrefer() {

    }
    std::vector<BoxLayout*> boxes_;
};
} // namespace ui

#endif