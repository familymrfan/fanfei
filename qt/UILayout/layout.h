#ifndef LAYOUT_H_
#define LAYOUT_H_

#include "widget.h"
#include "layout_item.h"
#include "layout_base_item.h"
#include <vector>

namespace ui
{
class Layout:public LayoutBaseItem
{
    friend class Widget;
public:
    virtual void AddItem(LayoutItem *item) {
        auto iter = layout_items_.begin();
        while (iter != layout_items_.end()) {
            if(*iter == item) {
                return ;
            }
            iter++;
        }
        layout_items_.push_back(item);
    }

    virtual bool InsertItem(uint32_t index, LayoutItem *item) {
        if(index < 0 || index > layout_items_.size())
            return false;
        auto iter = layout_items_.begin();
        while (iter != layout_items_.end()) {
            if(*iter == item) {
                return false;
            }
            iter++;
        }
        layout_items_.insert(layout_items_.begin()+index, item);
        return true;
    }

    virtual bool RemoveItem(LayoutItem *item) {
        auto iter = layout_items_.begin();
        while (iter != layout_items_.end()) {
            if(*iter == item) {
                layout_items_.erase(iter);
                return true;
            }
            iter++;
        }
        return false;
    }

    virtual bool RemoveItem(uint32_t index) {
        if(index < 0 || index > layout_items_.size())
            return false;
        layout_items_.erase(layout_items_.begin() + index);
        return true;
    }

    virtual LayoutItem* ItemAt(uint32_t  index) {
        if(index < 0 || index > layout_items_.size())
            return nullptr;
        return layout_items_[index];
    }
protected:
    Layout() {}

    virtual void SetGeometry(int32_t x, int32_t y, uint32_t width, uint32_t height) override {
        LayoutBaseItem::SetGeometry(x, y, width, height);
    }

    virtual void Move(int32_t x, int32_t y) override {
        LayoutBaseItem::Move(x, y);
    }

    virtual void ReSize(uint32_t width, uint32_t height) override {
        LayoutBaseItem::ReSize(width, height);
    }

    virtual void SetPreferWidth(uint32_t width) override {
        LayoutBaseItem::SetPreferWidth(width);
    }

    virtual void SetPreferHeight(uint32_t height) override {
        LayoutBaseItem::SetPreferHeight(height);
    }

    virtual void SetLimitMinWidth(uint32_t width) override {
        LayoutBaseItem::SetLimitMinWidth(width);
    }

    virtual void SetLimitMinHeight(uint32_t height) override {
        LayoutBaseItem::SetLimitMinHeight(height);
    }

    virtual void SetLimitMaxWidth(uint32_t width) override {
        LayoutBaseItem::SetLimitMaxWidth(width);
    }

    virtual void SetLimitMaxHeight(uint32_t height) override {
        LayoutBaseItem::SetLimitMaxWidth(height);
    }

    std::vector<LayoutItem*> layout_items_;
};
} // namespace ui

#endif // #ifndef LAYOUT_H