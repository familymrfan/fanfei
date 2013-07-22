#include "linear_box_layout.h"
#include "linear_box_layout_item.h"
#include "box_layout.h"
#include <vector>
#include <algorithm>
#include <cassert>
#include <memory>
#include "widget.h"

namespace ui
{
LinearBoxLayout::LinearBoxLayout() {
  
}

void LinearBoxLayout::SetWestSpace(LayoutBaseItem *item, uint32_t west_space) {
    LinearBoxLayoutItem *lbli = GetLinearBoxLayoutItem(item);
    assert(lbli);
    lbli->SetWestSpace(item, west_space);
}

void LinearBoxLayout::SetNorthSpace(LayoutBaseItem *item, uint32_t north_space) {
    LinearBoxLayoutItem *lbli = GetLinearBoxLayoutItem(item);
    assert(lbli);
    lbli->SetNorthSpace(item, north_space);
}

void LinearBoxLayout::SetEastSpace(LayoutBaseItem *item, uint32_t east_space) {
    LinearBoxLayoutItem *lbli = GetLinearBoxLayoutItem(item);
    assert(lbli);
    lbli->SetEastSpace(item, east_space);
}

void LinearBoxLayout::SetSouthSpace(LayoutBaseItem *item, uint32_t south_space) {
    LinearBoxLayoutItem *lbli = GetLinearBoxLayoutItem(item);
    assert(lbli);
    lbli->SetSouthSpace(item, south_space);
}

void LinearBoxLayout::SetAround(LayoutBaseItem *item, 
    uint32_t west_space, 
    uint32_t north_space, 
    uint32_t east_space, 
    uint32_t south_space) {
    SetWestSpace(item, west_space);
    SetNorthSpace(item, north_space);
    SetEastSpace(item, east_space);
    SetSouthSpace(item, south_space);
}

void LinearBoxLayout::SetValidGap(LayoutBaseItem *item,
    BoxLayoutItem::GapValid gap_valid,
    bool valid) {
    LinearBoxLayoutItem *lbli = GetLinearBoxLayoutItem(item);
    assert(lbli);
    lbli->SetValidGap(item, gap_valid, valid);
}

void LinearBoxLayout::SetStrechFactor(LayoutBaseItem* item, uint32_t strech_factor) {
    LinearBoxLayoutItem *lbli = GetLinearBoxLayoutItem(item);
    assert(lbli);
    lbli->SetStrechFactor(strech_factor);
}

void LinearBoxLayout::SetStrongElastic(LayoutBaseItem* item, bool strong_elastic) {
    LinearBoxLayoutItem *lbli = GetLinearBoxLayoutItem(item);
    assert(lbli);
    lbli->SetStrongElastic(strong_elastic);
}

void LinearBoxLayout::AddWidget(Widget* widget) {
    Widget* parent = GetParentWidget();
    assert(parent);
    parent->AddChild(widget);
    Layout::AddItem(std::make_shared<LinearBoxLayoutItem>(widget));
}

bool LinearBoxLayout::InsertWidget(uint32_t index, Widget *widget) {
    Widget* parent = GetParentWidget();
    assert(parent);
    parent->AddChild(widget);
    return Layout::InsertItem(index, std::make_shared<LinearBoxLayoutItem>(widget));
}

bool LinearBoxLayout::RemoveWidget(Widget *widget) {
    Widget* parent = GetParentWidget();
    assert(parent);
    parent->RemoveChild(widget);
    auto iter = layout_items_.begin();
    while (iter != layout_items_.end()) {
	if((*iter)->GetWidget() == widget) {
	    layout_items_.erase(iter);
	    return true;
	}
	iter++;
    }
    return false;
}
    
void LinearBoxLayout::AddLayout(Layout* layout) {
    Widget* parent = GetParentWidget();
    assert(parent);
    layout->SetParentWidget(parent);
    Layout::AddItem(std::make_shared<LinearBoxLayoutItem>(layout));
}

bool LinearBoxLayout::InsertLayout(uint32_t index, Layout *layout) {
    Widget* parent = GetParentWidget();
    assert(parent);
    layout->SetParentWidget(parent);
    return Layout::InsertItem(index, std::make_shared<LinearBoxLayoutItem>(layout));
}

bool LinearBoxLayout::RemoveLayout(Layout *layout) {
    layout->SetParentWidget(nullptr);
    layout->Empty();
    auto iter = layout_items_.begin();
    while (iter != layout_items_.end()) {
	if((*iter)->GetLayout() == layout) {
	    layout_items_.erase(iter);
	    return true;
	}
	iter++;
    }
    return false;
}

LinearBoxLayout::~LinearBoxLayout() {

}

void LinearBoxLayout::Relayout() {
    BoxToAllocHelper();
    if(IsUnderPrefer()) {
	DoUnderPrefer();
    } else {
	DoExceedPrefer();
    }
    AllocHelperToBox();
}

void LinearBoxLayout::BoxToAllocHelper() {
    alloc_sections_.clear();
    auto iter = layout_items_.begin();
    while(iter != layout_items_.end()) {
	AllocHelper helper;
	helper.box_item = reinterpret_cast<LinearBoxLayoutItem *>(iter->get());
	if(helper.box_item->IsEmpty()) {
	    iter++;
	    continue;
	}
	alloc_sections_.push_back(helper);
	iter++;
    }
}

bool LinearBoxLayout::IsStrongWeakAllInNoAlloc() {
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

void LinearBoxLayout::ResetTempAllocToNoAlloc() {
    auto iter = alloc_sections_.begin();
    while(iter != alloc_sections_.end()) {
	if(iter->status == AllocHelper::kTempAlloc) {
	    iter->status = AllocHelper::kNoAlloc;
	}
	iter++;
    }
}

LinearBoxLayoutItem* LinearBoxLayout::GetLinearBoxLayoutItem(LayoutBaseItem *item) {
    auto iter = layout_items_.begin();
    while (iter != layout_items_.end()) {
	if((*iter)->GetLayoutBaseItem() == item) {
	    return reinterpret_cast<LinearBoxLayoutItem*>(iter->get());
	}
	iter++;
    }
    return nullptr;
}

bool LinearBoxLayout::IsEmpty() {
    bool empty = true;
    auto iter = layout_items_.begin();
    while (iter != layout_items_.end()) {
	LinearBoxLayoutItem *lbli = reinterpret_cast<LinearBoxLayoutItem*>(iter->get());
	assert(lbli);
	if(lbli->IsEmpty()) {
	    iter++;
	    continue ;
	}
	empty = false;
	iter++;
    }
    return empty;
}
} // namespace ui
