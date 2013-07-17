#ifndef BOX_LAYOUT_ITEM_H_
#define BOX_LAYOUT_ITEM_H_

#include "layout_item.h"

namespace ui
{
class Widget;
class Layout;
class LayoutSpace;

class BoxLayoutItem:public LayoutItem
{
public:
    BoxLayoutItem(Widget* widget);
    BoxLayoutItem(Layout* layout);
    BoxLayoutItem(LayoutSpace* layout_space);

    enum GapValid {
        kInValid   =  0,
        kWestValid =  1,
        kNorthValid = 2,
        kEastValid =  4,
        kSouthValid = 8
    };

    void SetWestSpace(uint32_t west_space);
    void SetNorthSpace(uint32_t north_space);
    void SetEastSpace(uint32_t east_space);
    void SetSouthSpace(uint32_t south_space);
    void SetAround(uint32_t west_space, 
                   uint32_t north_space, 
                   uint32_t east_space, 
                   uint32_t south_space);
    
    void SetValidGap(GapValid gap_valid, bool valid = true);
    bool IsValidGap(GapValid gap_valid) const;

    uint32_t WestSpace() const;
    uint32_t NorthSpace() const;
    uint32_t EastSpace() const;
    uint32_t SouthSpace() const;
    
private:
    uint32_t west_space_;
    uint32_t north_space_;
    uint32_t east_space_;
    uint32_t south_space_;
    uint16_t gap_valid_;
};

} // namespace ui
#endif