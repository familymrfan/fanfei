#include "linear_box_layout_item.h"
#include "widget.h"
#include "layout.h"
#include "layout_space.h"
#include "box_layout.h"

namespace ui
{

LinearBoxLayoutItem::LinearBoxLayoutItem(Widget* widget):
    LayoutItem(widget),
    strech_factor_(1),
    strong_elastic_(false){
      
    box_layout_ = std::make_shared<BoxLayout>();
    box_layout_->SetParentWidget(widget->Parent());
    box_layout_->AddWidget(widget);
}

LinearBoxLayoutItem::LinearBoxLayoutItem(Layout* layout):
    LayoutItem(layout),
    strech_factor_(1),
    strong_elastic_(false) {
      
    box_layout_ = std::make_shared<BoxLayout>();
    box_layout_->SetParentWidget(layout->GetParentWidget());
    box_layout_->AddLayout(layout);
    box_layout_->SetAround(layout, 0, 0, 0, 0);
}

LinearBoxLayoutItem::LinearBoxLayoutItem(LayoutSpace* layout_space):
    LayoutItem(layout_space),
    strech_factor_(1),
    strong_elastic_(false){
  
}

void LinearBoxLayoutItem::SetStrechFactor(uint32_t strech_factor) {
    strech_factor_ = strech_factor;
}

uint32_t LinearBoxLayoutItem::StrechFactor() const {
    return strech_factor_;
}

void LinearBoxLayoutItem::SetStrongElastic(bool strong_elastic) {
    strong_elastic_ = strong_elastic;
}

bool LinearBoxLayoutItem::IsStrongElastic() const {
    return strong_elastic_;
}

bool LinearBoxLayoutItem::IsEmpty() {
    if(box_layout_) {
	return box_layout_->IsEmpty();
    }
    return true;
}

void LinearBoxLayoutItem::SetWestSpace(LayoutBaseItem *item, uint32_t west_space) {
    if(box_layout_) {
	box_layout_->SetWestSpace(item, west_space);
    }
}

void LinearBoxLayoutItem::SetNorthSpace(LayoutBaseItem *item, uint32_t north_space) {
    if(box_layout_) {
	box_layout_->SetNorthSpace(item, north_space);
    }
}

void LinearBoxLayoutItem::SetEastSpace(LayoutBaseItem *item, uint32_t east_space) {
    if(box_layout_) {
	box_layout_->SetEastSpace(item, east_space);
    }
}

void LinearBoxLayoutItem::SetSouthSpace(LayoutBaseItem *item, uint32_t south_space) {
    if(box_layout_) {
	box_layout_->SetSouthSpace(item, south_space);
    }
}

void LinearBoxLayoutItem::SetAround(LayoutBaseItem *item, 
    uint32_t west_space, 
    uint32_t north_space, 
    uint32_t east_space, 
    uint32_t south_space) {
    if(box_layout_) {
	box_layout_->SetAround(item, west_space, north_space, east_space, south_space);
    }
}

void LinearBoxLayoutItem::SetValidGap(LayoutBaseItem *item,
        BoxLayoutItem::GapValid gap_valid,
        bool valid) {
    if(box_layout_) {
	box_layout_->SetValidGap(item, gap_valid, valid);
    }
}

void LinearBoxLayoutItem::Move(int32_t x, int32_t y) {
    if(box_layout_) {
       box_layout_->Move(x, y);
    }
}

void LinearBoxLayoutItem::ReSize(uint32_t width, uint32_t height) {
    if(box_layout_) {
       box_layout_->ReSize(width, height);
    }
}

void LinearBoxLayoutItem::SetGeometry(int32_t x, int32_t y, uint32_t width, uint32_t height) {
    if(box_layout_) {
       box_layout_->SetGeometry(x, y, width, height);
    }
}

void LinearBoxLayoutItem::Relayout() {
    if(box_layout_) {
      box_layout_->Relayout();
    }
}

} // namespace ui