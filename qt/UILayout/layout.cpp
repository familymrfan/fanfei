#include "layout.h"
#include "layout_item.h"
#include "widget.h"
#include <cassert>

namespace ui
{
void Layout::AddItem(SharedLayoutItem item) {
    InsertItem(layout_items_.size(), item);
}

bool Layout::InsertItem(uint32_t index, SharedLayoutItem item) {
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

bool Layout::RemoveItem(SharedLayoutItem item) {
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

bool Layout::RemoveItem(uint32_t index) {
    if(index < 0 || index > layout_items_.size())
	return false;
    layout_items_.erase(layout_items_.begin() + index);
    return true;
}

Layout::SharedLayoutItem Layout::ItemAt(uint32_t  index) {
    if(index < 0 || index > layout_items_.size())
	return nullptr;
    return layout_items_[index];
}

void Layout::ResetPreferLimitSize() {
    for(auto item:layout_items_) {
      item->ResetPreferLimitSize();
    }
    SetLimitMinWidth(CalculateLimitMinWidth());
    SetLimitMinHeight(CalculateLimitMinHeight());
    SetLimitMaxWidth(CalculateLimitMaxWidth());
    SetLimitMaxHeight(CalculateLimitMaxHeight());
    SetPreferWidth(CalculatePreferWidth());
    SetPreferHeight(CalculatePreferHeight());
}

void Layout::SetGeometry(int32_t x, int32_t y, uint32_t width, uint32_t height) {
    LayoutBaseItem::SetGeometry(x, y, width, height);
}

void Layout::Move(int32_t x, int32_t y) {
    LayoutBaseItem::Move(x, y);
}

void Layout::ReSize(uint32_t width, uint32_t height){
    LayoutBaseItem::ReSize(width, height);
}

void Layout::SetPreferWidth(uint32_t width) {
    LayoutBaseItem::SetPreferWidth(width);
}

void Layout::SetPreferHeight(uint32_t height) {
    LayoutBaseItem::SetPreferHeight(height);
}

void Layout::SetLimitMinWidth(uint32_t width) {
    LayoutBaseItem::SetLimitMinWidth(width);
}

void Layout::SetLimitMinHeight(uint32_t height) {
    LayoutBaseItem::SetLimitMinHeight(height);
}

void Layout::SetLimitMaxWidth(uint32_t width) {
    LayoutBaseItem::SetLimitMaxWidth(width);
}

void Layout::SetLimitMaxHeight(uint32_t height) {
    LayoutBaseItem::SetLimitMaxHeight(height);
}

void Layout::SetParentWidget(Widget* widget) {
    parent_widget_ = widget;
}

Widget* Layout::GetParentWidget() const {
    return parent_widget_;
}

void Layout::Empty() {
    auto iter = layout_items_.begin();
    while(iter != layout_items_.end()) {
	auto item = (*iter);
	// skip unvisible item
	if(item->GetWidget()) {
	    item->GetWidget()->SetParent(nullptr);
	} else if(item->GetLayout()) {
	    item->GetLayout()->SetParentWidget(nullptr);
	    item->GetLayout()->Empty();
	}
	iter++;
    }
    layout_items_.clear();
}

bool Layout::IsEmpty() {
    return layout_items_.empty();
}
} // namespace ui