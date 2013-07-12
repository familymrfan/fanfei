#ifndef BUTTON_H_
#define BUTTON_H_


#include "layout_item.h"
#include "widget.h"
#include <QPushButton>

namespace ui
{
class Button:public Widget
{
public:
    Button() {
        fake_widget_ = new QPushButton;
    }

    virtual void SetText(const std::string& text) {
        ((QPushButton *)fake_widget_)->setText(text.c_str());
    }

    virtual uint32_t PreferWidth() override{
        return 200;
    }

    virtual uint32_t PreferHeight() override{
        return 100;
    }
};
} // namespace UI

#endif