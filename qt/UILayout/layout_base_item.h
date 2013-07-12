#ifndef LAYOUT_BASE_ITEM_H_
#define LAYOUT_BASE_ITEM_H_

namespace ui
{
#define MAX_LENGTH UINT32_MAX

class LayoutBaseItem
{
public:

    LayoutBaseItem():x_(0),
                     y_(0),
                     width_(0),
                     height_(0),
                     prefer_width_(0),
                     prefer_height_(0),
                     limit_min_width_(0),
                     limit_min_height_(0),
                     limit_max_width_(MAX_LENGTH),
                     limit_max_height_(MAX_LENGTH) {

    }

    virtual ~LayoutBaseItem() {}

    virtual void Move(int32_t x, int32_t y) {
        x_ = x;
        y_ = y;
    }

    virtual void ReSize(uint32_t width, uint32_t height) {
        width_ = width;
        height_ = height;
    }

    virtual void SetGeometry(int32_t x, int32_t y, uint32_t width, uint32_t height) {
        Move(x, y);
        ReSize(width, height);
    }

    virtual int32_t X() {
        return x_;
    }

    virtual int32_t Y() {
        return y_;
    }

    virtual uint32_t Width() {
        return width_;
    }

    virtual uint32_t Height() {
        return height_;
    }
    
    virtual void SetPreferWidth(uint32_t width) {
        prefer_width_ = width;
    }

    virtual uint32_t PreferWidth() {
        return prefer_width_;
    }

    virtual void SetPreferHeight(uint32_t height) {
        prefer_height_ = height;
    }

    virtual uint32_t PreferHeight() {
        return prefer_height_;
    }

    virtual void SetLimitMinWidth(uint32_t width) {
        limit_min_width_ = width;
    }

    virtual uint32_t LimitMinWidth() {
        return limit_min_width_;
    }

    virtual void SetLimitMinHeight(uint32_t height) {
        limit_min_height_ = height;
    }

    virtual uint32_t LimitMinHeight() {
        return limit_min_height_;
    }

    virtual void SetLimitMaxWidth(uint32_t width) {
        limit_max_width_ = width;
    }

    virtual uint32_t LimitMaxWidth() {
        return limit_max_width_;
    }

    virtual void SetLimitMaxHeight(uint32_t height) {
        limit_max_height_ = height;
    }

    virtual uint32_t LimitMaxHeight() {
        return limit_max_height_;
    }

    virtual void Relayout() = 0;
private:
    int32_t x_;
    int32_t y_;
    uint32_t width_;
    uint32_t height_;

    uint32_t prefer_width_;
    uint32_t prefer_height_;

    uint32_t limit_min_width_;
    uint32_t limit_min_height_;
    uint32_t limit_max_width_;
    uint32_t limit_max_height_;
};
} // namesapce ui

#endif // LAYOUT_BASE_ITEM