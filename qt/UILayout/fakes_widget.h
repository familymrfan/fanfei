#ifndef WIDGET_H_
#define WIDGET_H_

#include "fakes_factory.h"
#include "layout_item.h"

namespace UI
{
class Widget:public LayoutItem
{
public:
    virtual ~Widget() {}
    virtual void SetPerferSize(const Size& size) {
        prefer_size_ = size;
    }

protected:
    Size prefer_size_;
};
} // namespace UI

#endif