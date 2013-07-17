#include "box_layout_item.h"

namespace ui
{
BoxLayoutItem::BoxLayoutItem(Widget* widget):
    LayoutItem(widget),
    west_space_(0),
    north_space_(0),
    east_space_(0),
    south_space_(0),
    gap_valid_(0) {

}
    
BoxLayoutItem::BoxLayoutItem(Layout* layout):
    LayoutItem(layout),
    west_space_(0),
    north_space_(0),
    east_space_(0),
    south_space_(0),
    gap_valid_(0) {

}

BoxLayoutItem::BoxLayoutItem(LayoutSpace* layout_space):
    LayoutItem(layout_space),
    west_space_(0),
    north_space_(0),
    east_space_(0),
    south_space_(0),
    gap_valid_(0) {

}
  
void BoxLayoutItem::SetWestSpace(uint32_t west_space) {
    west_space_ = west_space;
    SetValidGap(kWestValid);
}

void BoxLayoutItem::SetNorthSpace(uint32_t north_space) {
    north_space_ = north_space;
    SetValidGap(kNorthValid);
}

void BoxLayoutItem::SetEastSpace(uint32_t east_space) {
    east_space_ = east_space;
        SetValidGap(kEastValid);
}

void BoxLayoutItem::SetSouthSpace(uint32_t south_space) {
    south_space_ = south_space;
    SetValidGap(kSouthValid);
}

void BoxLayoutItem::SetAround(uint32_t west_space, 
                   uint32_t north_space, 
                   uint32_t east_space, 
                   uint32_t south_space) {
    SetWestSpace(west_space);
    SetNorthSpace(north_space);
    SetEastSpace(east_space);
    SetSouthSpace(south_space);
}

void BoxLayoutItem::SetValidGap(GapValid gap_valid, bool valid) {
    if(valid) {
        gap_valid_ |= gap_valid;
    } else {
        gap_valid_ &= ~gap_valid;
    }
}

bool BoxLayoutItem::IsValidGap(GapValid gap_valid) const {
    return (gap_valid_ & gap_valid) == gap_valid;
}

uint32_t BoxLayoutItem::WestSpace() const {
    return west_space_;
}

uint32_t BoxLayoutItem::NorthSpace() const {
    return north_space_;
}

uint32_t BoxLayoutItem::EastSpace() const {
    return east_space_;
}

uint32_t BoxLayoutItem::SouthSpace() const {
    return south_space_;
}
    
} // namespace ui