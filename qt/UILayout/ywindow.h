#ifndef WINDOW_H_
#define WINDOW_H_

#include "widget.h"

namespace ui
{
    class Window:public Widget
    {    
    public:
        Window() {
           fake_widget_ = new QWidget;
        }
    };
} // namespace UI

#endif