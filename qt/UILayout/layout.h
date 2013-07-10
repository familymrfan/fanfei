#ifndef LAYOUT_H_
#define LAYOUT_H_

#include "widget.h"
#include "layout_item.h"
#include <vector>

namespace ui
{

class Layout:public LayoutItem
{
    friend class Widget;
public:
    virtual void AddItem(LayoutItem *item) {
        layout_items_.push_back(item);
    }

    virtual bool InsertItem(int32_t index, LayoutItem *item) {
        if(index < 0 || index > layout_items_.size())
            return false;
        layout_items_.insert(layout_items_.begin()+index, item);
        return true;
    }

    virtual void RemoveItem(LayoutItem *item) {
        auto iter = layout_items_.begin();
        while (iter != layout_items_.end())
        {
            if(*iter == item) {
                layout_items_.erase(iter);
                break;
            }
            iter++;
        }
    }

    virtual LayoutItem* ItemAt(int32_t  index) const {
        if(index < 0 || index > layout_items_.size())
            return nullptr;
        return layout_items_[index];
    }
protected:
    virtual void SetGeometry(int32_t x, int32_t y, int32_t width, int32_t height) override {
        LayoutItem::SetGeometry(x, y, width, height);
    }

    virtual void Move(int32_t x, int32_t y) {
        LayoutItem::Move(x, y);
    }

    virtual void ReSize(int32_t width, int32_t height) {
        LayoutItem::ReSize(width, height);
    }

    std::vector<LayoutItem*> layout_items_;
};

} // namespace ui

#endif // #ifndef LAYOUT_H