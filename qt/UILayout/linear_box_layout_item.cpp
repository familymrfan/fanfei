#include "linear_box_layout_item.h"
#include "widget.h"
#include "layout.h"
#include "layout_space.h"

namespace ui
{

LinearBoxLayoutItem::LinearBoxLayoutItem(Widget* widget):
    LayoutItem(widget),
    strech_factor_(1),
    strong_elastic_(false){
  
}

LinearBoxLayoutItem::LinearBoxLayoutItem(Layout* layout):
    LayoutItem(layout),
    strech_factor_(1),
    strong_elastic_(false){
  
}

LinearBoxLayoutItem::LinearBoxLayoutItem(LayoutSpace* layout_space):
    LayoutItem(layout_space),
    strech_factor_(1),
    strong_elastic_(false){
  
}

void LinearBoxLayoutItem::SetStrechFactor(uint32_t strech_factor) {
    strech_factor_ = strech_factor;
}

uint32_t LinearBoxLayoutItem::StrechFactor() const {
    return strech_factor_;
}

void LinearBoxLayoutItem::SetStrongElastic(bool strong_elastic) {
    strong_elastic_ = strong_elastic;
}

bool LinearBoxLayoutItem::IsStrongElastic() const {
    return strong_elastic_;
}

} // namespace ui