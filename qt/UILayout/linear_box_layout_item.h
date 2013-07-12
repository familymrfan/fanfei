#ifndef LINEAR_BOX_LAYOUT_ITEM_H_
#define LINEAR_BOX_LAYOUT_ITEM_H_

#include "layout_item.h"

namespace ui
{

class LinearBoxLayoutItem:public LayoutItem
{
public:
    LinearBoxLayoutItem(LayoutBaseItem* li):
        LayoutItem(li),
        strech_factor_(0),
        strong_elastic_(false) {

    }

    void SetStrechFactor(uint32_t strech_factor) {
        strech_factor_ = strech_factor;
    }

    uint32_t StrechFactor() const {
        return strech_factor_;
    }

    void SetStrongElastic(bool strong_elastic) {
        strong_elastic_ = strong_elastic;
    }

    bool IsStrongElastic() const {
        return strong_elastic_;
    }
protected:
    uint32_t strech_factor_;
    bool    strong_elastic_;
};

} // namespace ui
#endif // LINEAR_BOX_LAYOUT_ITEM_H_