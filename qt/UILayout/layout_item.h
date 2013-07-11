#ifndef LAYOUT_ITEM_H_
#define LAYOUT_ITEM_H_

#include <stdint.h>
#include "layout_item_side_space.h"
#include "layout_item_limited_size.h"
#include "layout_item_capacity_alloc.h"

namespace ui
{

class LayoutItem : public LayoutItemSideSpace, 
                   public LayoutItemLimitedSize,
                   public LayoutItemCapacityAlloc
{
public:
    virtual ~LayoutItem() {}
    virtual void Update() = 0;
    
    // 实际布局与大小
    virtual void Move(int32_t x, int32_t y) {
        x_ = x;
        y_ = y;
    }

    virtual void ReSize(int32_t width, int32_t height) {
        width_ = width;
        height_ = height;
    }

    virtual int32_t X() const {
        return x_;
    }

    virtual int32_t Y() const {
        return y_;
    }

    virtual int32_t Width() const {
        return width_;
    }

    virtual int32_t Height() const {
        return height_;
    }

    virtual void SetGeometry(int32_t x, int32_t y, int32_t width, int32_t height) {
        Move(x, y);
        ReSize(width, height);
    }

protected:
    LayoutItem():x_(0),
                 y_(0),
                 width_(0),
                 height_(0) {

    }

    //实际布局与大小
    int32_t x_;
    int32_t y_;
    int32_t width_;
    int32_t height_;
};

} // namespace ui
#endif