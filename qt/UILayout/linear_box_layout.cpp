#include "linear_box_layout.h"
#include "linear_box_layout_item.h"
#include "box_layout.h"
#include <vector>
#include <algorithm>
#include <cassert>

namespace ui
{
LinearBoxLayout::LinearBoxLayout() {
  
}

void LinearBoxLayout::SetWestSpace(LayoutBaseItem *item, uint32_t west_space) {
    BoxLayoutItem *bli = GetBoxLayoutItem(item);
    assert(bli);
    bli->SetWestSpace(west_space);
}

void LinearBoxLayout::SetNorthSpace(LayoutBaseItem *item, uint32_t north_space) {
    BoxLayoutItem *bli = GetBoxLayoutItem(item);
    assert(bli);
    bli->SetNorthSpace(north_space);
}

void LinearBoxLayout::SetEastSpace(LayoutBaseItem *item, uint32_t east_space) {
    BoxLayoutItem *bli = GetBoxLayoutItem(item);
    assert(bli);
    bli->SetEastSpace(east_space);
}

void LinearBoxLayout::SetSouthSpace(LayoutBaseItem *item, uint32_t south_space) {
    BoxLayoutItem *bli = GetBoxLayoutItem(item);
    assert(bli);
    bli->SetSouthSpace(south_space);
}

void LinearBoxLayout::SetAround(LayoutBaseItem *item, 
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

void LinearBoxLayout::SetValidGap(LayoutBaseItem *item,
    BoxLayoutItem::GapValid gap_valid,
    bool valid) {
	BoxLayoutItem *bli = GetBoxLayoutItem(item);
	assert(bli);
	bli->SetValidGap(gap_valid, valid);
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
    auto box = new BoxLayout;
    box->SetParentWidget(parent);
    box->AddWidget(widget);
    LinearBoxLayoutItem *lbli = new LinearBoxLayoutItem(box);
    Layout::AddItem(lbli);
}

bool LinearBoxLayout::InsertWidget(uint32_t index, Widget *widget) {
    Widget* parent = GetParentWidget();
    assert(parent);
    parent->AddChild(widget);
    auto box = new BoxLayout;
    box->SetParentWidget(parent);
    box->AddWidget(widget);
    LinearBoxLayoutItem *lbli = new LinearBoxLayoutItem(box);
    return Layout::InsertItem(index, lbli);
}

bool LinearBoxLayout::RemoveWidget(Widget *widget) {
    Widget* parent = GetParentWidget();
    assert(parent);
    parent->RemoveChild(widget);
    auto iter = layout_items_.begin();
    while (iter != layout_items_.end()) {
	BoxLayout *box = reinterpret_cast<BoxLayout *>((*iter)->GetLayoutBaseItem());
	LayoutBaseItem *lbli = box->ItemAt(0)->GetLayoutBaseItem();
	if(lbli == widget) {
	    delete box;
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
    auto box = new BoxLayout;
    box->SetParentWidget(parent);
    box->AddLayout(layout);
    LinearBoxLayoutItem *lbli = new LinearBoxLayoutItem(box);
    Layout::AddItem(lbli);
}

bool LinearBoxLayout::InsertLayout(uint32_t index, Layout *layout) {
    Widget* parent = GetParentWidget();
    assert(parent);
    layout->SetParentWidget(parent);
    auto box = new BoxLayout;
    box->SetParentWidget(parent);
    box->AddLayout(layout);
    LinearBoxLayoutItem *lbli = new LinearBoxLayoutItem(box);
    return Layout::InsertItem(index, lbli);
}

bool LinearBoxLayout::RemoveLayout(Layout *layout) {
    Widget* parent = GetParentWidget();
    assert(parent);
    layout->SetParentWidget(nullptr);
    auto iter = layout_items_.begin();
    while (iter != layout_items_.end()) {
	BoxLayout *box = reinterpret_cast<BoxLayout *>((*iter)->GetLayoutBaseItem());
	LayoutBaseItem *lbli = box->ItemAt(0)->GetLayoutBaseItem();
	if(lbli == layout) {
	    delete box;
	    layout_items_.erase(iter);
	    return true;
	}
	iter++;
    }
    return false;
}

LinearBoxLayout::~LinearBoxLayout() {
    for(uint32_t i = 0;i<layout_items_.size();i++) {
	LayoutBaseItem *bli = layout_items_[i]->GetLayoutBaseItem();
	assert(bli);
	delete bli;
	layout_items_.erase(layout_items_.begin() + i);
    }
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
	helper.box_item = reinterpret_cast<LinearBoxLayoutItem *>(*iter);
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

BoxLayoutItem* LinearBoxLayout::GetBoxLayoutItem(LayoutBaseItem *item) {
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

} // namespace ui
