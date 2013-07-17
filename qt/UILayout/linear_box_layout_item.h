#ifndef LINEAR_BOX_LAYOUT_ITEM_H_
#define LINEAR_BOX_LAYOUT_ITEM_H_

#include "layout_item.h"

namespace ui
{
class Widget;
class Layout;
class LayoutSpace;
  
class LinearBoxLayoutItem:public LayoutItem
{
public:
    LinearBoxLayoutItem(Widget* widget);
    LinearBoxLayoutItem(Layout* layout);
    LinearBoxLayoutItem(LayoutSpace* layout_space);

    void SetStrechFactor(uint32_t strech_factor);
    uint32_t StrechFactor() const;
    void SetStrongElastic(bool strong_elastic);
    bool IsStrongElastic() const;
    
protected:
    uint32_t strech_factor_;
    bool    strong_elastic_;
};

} // namespace ui
#endif // LINEAR_BOX_LAYOUT_ITEM_H_