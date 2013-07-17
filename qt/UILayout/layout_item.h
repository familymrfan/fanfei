#ifndef LAYOUT_ITEM_H_
#define LAYOUT_ITEM_H_

#include "stdint.h"

namespace ui
{
class Widget;
class Layout;
class LayoutSpace;
class LayoutBaseItem;

class LayoutItem
{
public:
    LayoutItem(Widget* widget);
    LayoutItem(Layout* layout);
    LayoutItem(LayoutSpace* layout_space);
    
    virtual ~LayoutItem() {}
public:
    void SetGeometry(int32_t x, int32_t y, uint32_t width, uint32_t height);
    void Relayout();
    Widget* GetWidget() const;
    Layout* GetLayout() const;
    LayoutSpace* GetLayoutSpace() const;
    LayoutBaseItem* GetLayoutBaseItem() const;
    
private:
    Widget* widget_;
    Layout* layout_;
    LayoutSpace* layout_space_;
};

} // namespace ui
#endif