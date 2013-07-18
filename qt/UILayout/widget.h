#ifndef WIDGET_H_
#define WIDGET_H_

#include <QWidget>
#include "layout_base_item.h"

namespace ui
{

class Layout;
class Widget:public LayoutBaseItem
{
    typedef QWidget FakeWidget;
public:
    Widget();
    virtual ~Widget();

    virtual void AddChild(Widget* widget);
    virtual void RemoveChild(Widget* widget);
    Widget* ChildAt(uint32_t index);
    uint32_t ChildrenNum() const;
    virtual void SetParent(Widget* widget);
    virtual void SetGeometry(int32_t x, int32_t y, uint32_t width, uint32_t height) override;
    virtual void Show();
    virtual void Hide();
    bool IsVisible() const;
    //Fake remove later
    FakeWidget* GetFakeWidget();
    void SetLayout(Layout* layout);
    virtual uint32_t Width() override;
    virtual uint32_t Height() override;
    virtual void ResetPreferLimitSize() override;
    
public:
    virtual void Relayout() override;
protected:
    std::vector<Widget*> children_;
    std::vector<Layout*> layer_;
    Widget* parent_;
    //Fake remove later
    FakeWidget *fake_widget_;
};
} // namespace ui

#endif