#ifndef LAYOUT_H_
#define LAYOUT_H_

#include "widget.h"
#include "layout_base_item.h"
#include "layout_item.h"
#include <vector>

namespace ui
{
class LayoutItem;  
  
class Layout:public LayoutBaseItem
{
    friend class Widget;
    friend class LayoutItem;
public:
    virtual void AddItem(LayoutItem *item);
    virtual bool InsertItem(uint32_t index, LayoutItem *item);
    virtual bool RemoveItem(LayoutItem *item);
    virtual bool RemoveItem(uint32_t index);
    virtual LayoutItem* ItemAt(uint32_t  index);
    virtual void ResetPreferLimitSize() override;
public:
    virtual void AddWidget(Widget* widget) = 0;
    virtual bool InsertWidget(uint32_t index, Widget *widget) = 0;
    virtual bool RemoveWidget(Widget *widget) = 0;
    
    virtual void AddLayout(Layout* layout) = 0;
    virtual bool InsertLayout(uint32_t index, Layout *layout) = 0;
    virtual bool RemoveLayout(Layout *layout) = 0;
    
    void SetParentWidget(Widget* widget);
    Widget* GetParentWidget() const;
    
    virtual void Empty();
    virtual bool IsEmpty();
protected:
    Layout():parent_widget_(nullptr) {}

    virtual uint32_t CalculateLimitMinWidth() = 0;
    virtual uint32_t CalculateLimitMinHeight() = 0;
    virtual uint32_t CalculateLimitMaxWidth() = 0;
    virtual uint32_t CalculateLimitMaxHeight() = 0;
    virtual uint32_t CalculatePreferWidth() = 0;
    virtual uint32_t CalculatePreferHeight() = 0;
    
    virtual void SetGeometry(int32_t x, int32_t y, uint32_t width, uint32_t height) override;
    virtual void Move(int32_t x, int32_t y) override;
    virtual void ReSize(uint32_t width, uint32_t height) override;
    virtual void SetPreferWidth(uint32_t width) override;
    virtual void SetPreferHeight(uint32_t height) override;
    virtual void SetLimitMinWidth(uint32_t width) override;
    virtual void SetLimitMinHeight(uint32_t height) override;
    virtual void SetLimitMaxWidth(uint32_t width) override;
    virtual void SetLimitMaxHeight(uint32_t height) override;
    
    std::vector<LayoutItem*> layout_items_;
    Widget* parent_widget_;
};
} // namespace ui

#endif // #ifndef LAYOUT_H