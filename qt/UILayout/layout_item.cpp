#include "layout_item.h"

#include "widget.h"
#include "layout.h"
#include "layout_space.h"
#include "layout_base_item.h"

namespace ui
{
LayoutItem::LayoutItem(Widget* widget):
    widget_(widget),
    layout_(nullptr),
    layout_space_(nullptr) {

}

LayoutItem::LayoutItem(Layout* layout):
    layout_(layout), 
    widget_(nullptr),
    layout_space_(nullptr) {

}

LayoutItem::LayoutItem(LayoutSpace* layout_space):
    layout_space_(layout_space), 
    widget_(nullptr),
    layout_(nullptr) {

}

void LayoutItem::SetGeometry(int32_t x, int32_t y, uint32_t width, uint32_t height) {
    if(widget_) {
	widget_->SetGeometry(x, y, width, height);
    } else if(layout_) {
	layout_->SetGeometry(x, y, width, height);
    }
}

void LayoutItem::Relayout() {
    if(widget_) {
	widget_->Relayout();
    } else if(layout_) {
	layout_->Relayout();
    }
}

Widget* LayoutItem::GetWidget() const {
    return widget_;
}

Layout* LayoutItem::GetLayout() const {
    return layout_;
}

LayoutSpace* LayoutItem::GetLayoutSpace() const {
    return layout_space_;
}

LayoutBaseItem* LayoutItem::GetLayoutBaseItem() const {
    if(widget_) {
      return reinterpret_cast<LayoutBaseItem *>(widget_);
    } else if(layout_) {
      return reinterpret_cast<LayoutBaseItem *>(layout_);
    } else if(layout_space_) {
      return reinterpret_cast<LayoutBaseItem *>(layout_space_);
    } else {
      return nullptr;
    }
}

} // namespace ui