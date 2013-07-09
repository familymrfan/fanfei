#ifndef WIDGET_H_
#define WIDGET_H_

#include "layout_item.h"
#include <QWidget>
#include <vector>

namespace ui
{
class Widget:public LayoutItem
{
    typedef QWidget FakeWidget;
public:
    virtual ~Widget() {}

    virtual void AddChild(Widget* widget) {
        if(fake_widget_ != nullptr) {
            widget->GetFakeWidget()->setParent(fake_widget_);
        }
        children_.push_back(widget);
    }

    virtual void SetParent(Widget* widget) {
        if(fake_widget_ != nullptr) {
            fake_widget_->setParent(widget->GetFakeWidget());
        }
        parent_ = widget;
    }

    virtual void SetGeometry(int32_t x, int32_t y, int32_t width, int32_t height) {
        fake_widget_->setGeometry(x, y, width, height);
        LayoutItem::SetGeometry(x, y, width, height);
    }

    virtual void Show() {
        fake_widget_->show();
    }

    virtual void Hide() {
        fake_widget_->hide();
    }

    //Fake remove later
    FakeWidget* GetFakeWidget() {
        return fake_widget_;
    }

protected:
    Widget()
        :parent_(nullptr),
        fake_widget_(nullptr){

    }

    std::vector<Widget*> children_;
    Widget* parent_;

    //Fake remove later
    FakeWidget *fake_widget_;
};
} // namespace UI

#endif