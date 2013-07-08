#ifndef BUTTON_H_
#define BUTTON_H_

#include "fakes_widget.h"
#include "fakes_factory.h"
#include "layout_item.h"
#include "fakes_window.h"
#include <QPushButton>

namespace UI
{
    class Button:public Widget
    {
        typedef QPushButton FakeWidget;
        typedef QWidget FakeWidgetParent;
    public:
        Button(Window* parent) {
            FakesFactory<FakeWidget,FakeWidgetParent> factory;
            fake_widget_ = factory.NewFakes(parent->GetWindow());
            fake_widget_->setText("My name is layout !");
            fake_widget_->show();
        }

        ~Button() {
            FakesFactory<FakeWidget> factory;
            factory.DelFakes(fake_widget_);
        }
    protected:
        FakeWidget *fake_widget_;
    };
} // namespace UI

#endif