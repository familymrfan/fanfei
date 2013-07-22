#ifndef LINEAR_BOX_LAYOUT_ITEM_H_
#define LINEAR_BOX_LAYOUT_ITEM_H_

#include "layout_item.h"
#include "box_layout_item.h"
#include <memory>
#include "stdint.h"

namespace ui
{
class Widget;
class Layout;
class LayoutSpace;
class BoxLayout;

class LinearBoxLayoutItem:public LayoutItem
{
public:
    LinearBoxLayoutItem(Widget* widget);
    LinearBoxLayoutItem(Layout* layout);
    LinearBoxLayoutItem(LayoutSpace* layout_space);

    void SetWestSpace(LayoutBaseItem *item, uint32_t west_space);
    void SetNorthSpace(LayoutBaseItem *item, uint32_t north_space);
    void SetEastSpace(LayoutBaseItem *item, uint32_t east_space);
    void SetSouthSpace(LayoutBaseItem *item, uint32_t south_space);
    void SetAround(LayoutBaseItem *item, 
        uint32_t west_space, 
        uint32_t north_space, 
        uint32_t east_space, 
        uint32_t south_space);
    void SetValidGap(LayoutBaseItem *item,
        BoxLayoutItem::GapValid gap_valid,
        bool valid = true);
    
    void SetStrechFactor(uint32_t strech_factor);
    uint32_t StrechFactor() const;
    void SetStrongElastic(bool strong_elastic);
    bool IsStrongElastic() const;
    bool IsEmpty();
    
    virtual void Move(int32_t x, int32_t y) override ;
    virtual void ReSize(uint32_t width, uint32_t height) override ;
    virtual void SetGeometry(int32_t x, int32_t y, uint32_t width, uint32_t height) override;
    virtual void Relayout()  override;
protected:
    uint32_t strech_factor_;
    bool    strong_elastic_;
    std::shared_ptr<BoxLayout> box_layout_;
};

} // namespace ui
#endif // LINEAR_BOX_LAYOUT_ITEM_H_