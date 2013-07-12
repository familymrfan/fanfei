#ifndef LAYOUT_ITEM_H_
#define LAYOUT_ITEM_H_

#include <stdint.h>
#include "layout_base_item.h"

namespace ui
{
class LayoutItem
{
public:
    LayoutItem(LayoutBaseItem* li):li_(li) {}
    virtual ~LayoutItem() {}
public:
    void SetGeometry(int32_t x, int32_t y, uint32_t width, uint32_t height) {
        if(li_) {
            li_->SetGeometry(x, y, width, height);
        }
    }

    void Relayout() {
        if(li_) {
            li_->Relayout();
        }
    }

    LayoutBaseItem* GetLayoutBaseItem() const {
        return li_;
    }
private:
    LayoutBaseItem* li_;
};

} // namespace ui
#endif