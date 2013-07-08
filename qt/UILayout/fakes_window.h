#ifndef WINDOW_H_
#define WINDOW_H_

#include "fakes_factory.h"
#include "layout_item.h"

#include "fakes_widget.h"

namespace UI
{
    class Window:public Widget
    {
        typedef QWidget FakeWidget;
    public:
        Window() {
            FakesFactory<FakeWidget> factory;
            fake_widget_ = factory.NewFakes();
            fake_widget_->show();
        }

        ~Window() {
            FakesFactory<FakeWidget> factory;
            factory.DelFakes(fake_widget_);
        }

        FakeWidget* GetWindow() const {
            return fake_widget_;
        }
    protected:
        FakeWidget *fake_widget_;
    };
} // namespace UI

#endif