#ifndef BOX_LAYOUT_ITEM_H_
#define BOX_LAYOUT_ITEM_H_

#include "layout_item.h"

namespace ui
{

class BoxLayoutItem:public LayoutItem
{
public:
    BoxLayoutItem(LayoutBaseItem* li):
        LayoutItem(li),
        west_space_(0),
        north_space_(0),
        east_space_(0),
        south_space_(0),
        gap_valid_(0) {

    }

    enum GapValid {
        kInValid   =  0,
        kWestValid =  1,
        kNorthValid = 2,
        kEastValid =  4,
        kSouthValid = 8
    };

    void SetWestSpace(uint32_t west_space) {
        west_space_ = west_space;
        SetValidGap(kWestValid);
    }

    void SetNorthSpace(uint32_t north_space) {
        north_space_ = north_space;
        SetValidGap(kNorthValid);
    }

    void SetEastSpace(uint32_t east_space) {
        east_space_ = east_space;
        SetValidGap(kEastValid);
    }

    void SetSouthSpace(uint32_t south_space) {
        south_space_ = south_space;
        SetValidGap(kSouthValid);
    }

    void SetAround(uint32_t west_space, 
                   uint32_t north_space, 
                   uint32_t east_space, 
                   uint32_t south_space) {
        SetWestSpace(west_space);
        SetNorthSpace(north_space);
        SetEastSpace(east_space);
        SetSouthSpace(south_space);
    }

    void SetValidGap(GapValid gap_valid, bool valid = true) {
        if(valid) {
            gap_valid_ |= gap_valid;
        }
        else {
            gap_valid_ &= ~gap_valid;
        }
    }

    bool IsValidGap(GapValid gap_valid) const {
        return (gap_valid_ & gap_valid) == gap_valid;
    }

    uint32_t WestSpace() const {
        return west_space_;
    }

    uint32_t NorthSpace() const {
        return north_space_;
    }

    uint32_t EastSpace() const {
        return east_space_;
    }

    uint32_t SouthSpace() const {
        return south_space_;
    }
private:
    uint32_t west_space_;
    uint32_t north_space_;
    uint32_t east_space_;
    uint32_t south_space_;
    uint16_t gap_valid_;
};

} // namespace ui
#endif