#include "hboxlayout.h"
#include "layout.h"
#include "box_layout.h"
#include <vector>
#include <algorithm>
#include <cassert>
#include "linear_box_layout_item.h"

namespace ui
{
HBoxLayout::HBoxLayout() {

}

uint32_t HBoxLayout::CalculateLimitMinWidth() {
    uint32_t width = 0;
    for (LayoutItem* item:layout_items_) {
	LayoutBaseItem *base_item = item->GetLayoutBaseItem();
	assert(base_item);
	width += base_item->LimitMinWidth();
    }
    return width;
}

uint32_t HBoxLayout::CalculateLimitMinHeight() {
    uint32_t height = 0;
    for (LayoutItem* item:layout_items_) {
	LayoutBaseItem *base_item = item->GetLayoutBaseItem();
	assert(base_item);
	if(base_item->LimitMinHeight() > height) {
	    height = base_item->LimitMinHeight();
	}
    }
    return height;
}

uint32_t HBoxLayout::CalculateLimitMaxWidth() {
    uint32_t width = MAX_LENGTH;
    for (LayoutItem* item:layout_items_) {
	LayoutBaseItem *base_item = item->GetLayoutBaseItem();
	if(width < MAX_LENGTH - base_item->LimitMaxWidth()) {
	    width += base_item->LimitMaxWidth();
	}
    }
    return width;
}

uint32_t HBoxLayout::CalculateLimitMaxHeight() {
    uint32_t height = MAX_LENGTH;
    for (LayoutItem* item:layout_items_) {
	LayoutBaseItem *base_item = item->GetLayoutBaseItem();
	if(base_item->LimitMaxHeight() < height) {
	    height = base_item->LimitMaxHeight();
	}
    }
    return height;
}

uint32_t HBoxLayout::CalculatePreferWidth() {
    uint32_t width = 0;
    for (LayoutItem* item:layout_items_) {
	LayoutBaseItem *base_item = item->GetLayoutBaseItem();
	width += std::max(base_item->LimitMinWidth(), base_item->PreferWidth());
    }
    return width;
}

uint32_t HBoxLayout::CalculatePreferHeight() {
    uint32_t height = 0, hign_height = 0;
    for (LayoutItem* item:layout_items_) {
	LayoutBaseItem *base_item = item->GetLayoutBaseItem();
	hign_height = std::max(base_item->LimitMinHeight(), base_item->PreferHeight());
	if(hign_height > height) {
	    height = hign_height;
	}
    }
    return height;
}

bool HBoxLayout::IsUnderPrefer() {
    return Width() < PreferWidth();
}

void HBoxLayout::DoUnderPrefer() {
    uint32_t alloc_size = Width();
    uint32_t sum_factor = 0;

    auto iter = alloc_sections_.begin();
    while(iter != alloc_sections_.end()) {
	LayoutBaseItem* box = iter->box_item->GetLayoutBaseItem();
	assert(box);
	if(box->LimitMinWidth() > box->PreferWidth()) {
	    iter->section = box->LimitMinWidth();
	    iter->status = AllocHelper::kAlloc;
	    alloc_size -= iter->section;
	} else {
	    sum_factor += box->PreferWidth();
	}
	iter++;
    }

    iter = alloc_sections_.begin();
    while(iter != alloc_sections_.end()) {
	LayoutBaseItem* box = iter->box_item->GetLayoutBaseItem();
	assert(box);
	if(iter->status == AllocHelper::kNoAlloc) {
	    iter->section = (uint32_t)((float)alloc_size/sum_factor*box->PreferWidth());
	}
	iter++;
    }
}

void HBoxLayout::DoExceedPrefer() {
    uint32_t alloc_size = Width();
    uint32_t sum_factor = 0;

    bool strong = IsStrongWeakAllInNoAlloc();

    auto iter = alloc_sections_.begin();
    while(iter != alloc_sections_.end()) {
	LayoutBaseItem* box = iter->box_item->GetLayoutBaseItem();
	assert(box);

	if(iter->box_item->StrechFactor() == 0 || (strong && !iter->box_item->IsStrongElastic())) {
	    if(box->PreferWidth() < box->LimitMinWidth()) {
	      iter->section = box->LimitMinWidth();
	    } else if(box->PreferWidth() > box->LimitMaxWidth()) {
	      iter->section = box->LimitMaxWidth();
	    } else {
	      iter->section = box->PreferWidth();
	    }
	    iter->status = AllocHelper::kAlloc;
	    alloc_size -= iter->section;
	} else {
	    sum_factor += iter->box_item->StrechFactor();
	}
	iter++;
    }
    AllocSectionByStrechFactor(alloc_size, sum_factor);
}

void HBoxLayout::AllocHelperToBox() {
    auto iter = alloc_sections_.begin();
    int32_t pre_x = X();
    while(iter != alloc_sections_.end()) {
	iter->box_item->SetGeometry(pre_x, Y(), iter->section, Height());
	iter->box_item->Relayout();
	pre_x += iter->section;
	iter++;
    }
}

void HBoxLayout::AllocSectionByStrechFactor(uint32_t alloc_size, uint32_t sum_factor) {
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
	    LayoutBaseItem* box = first->box_item->GetLayoutBaseItem();
	    first->section = (uint32_t)((float)alloc_size/sum_factor*first->box_item->StrechFactor());
	    if(first->section < box->LimitMinWidth()) {
		first->section = box->LimitMinWidth();
		alloc = true;
	    } else if (first->section > box->LimitMaxWidth()) {
		first->section = box->LimitMaxWidth();
		alloc = true;
	    } else if(first->section < box->PreferWidth()){
		first->section = box->PreferWidth();
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
		    if(iter->status != AllocHelper::kNoAlloc) {
			alloc_size -= iter->section;
		    } else {
			sum_factor += iter->box_item->StrechFactor();
		    }
		    iter++;
		}
	    } else {
		alloc_size -= first->section;
		sum_factor -= first->box_item->StrechFactor();
	    }
	    
	    AllocSectionByStrechFactor(alloc_size, sum_factor);
	}
    }
}
} // namespace ui