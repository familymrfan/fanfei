#ifndef LAYOUT_ITEM_H_
#define LAYOUT_ITEM_H_

#include <stdint.h>

class LayoutItem
{
public:
    enum GapValid {
        kWestValid =  1,
        kNorthValid = 2,
        kEastValid =  4,
        kSouthValid = 8
    };

    //TODO(fanfei):make common
    struct Size
    {
        Size():width_(0), height_(0) {

        }

        Size(int width, int height):
            width_(width),
            height_(height) {

        }
        int32_t width_;
        int32_t height_;
    };

    virtual ~LayoutItem() {}

    virtual void SetWestSpace(int32_t west_space) {
        west_space_ = west_space;
        SetValidGap(kWestValid);
    }

    virtual void SetNorthSpace(int32_t north_space) {
        north_space_ = north_space;
        SetValidGap(kNorthValid);
    }

    virtual void SetEastSpace(int32_t east_space) {
        east_space_ = east_space;
        SetValidGap(kEastValid);
    }

    virtual void SetSouthSpace(int32_t south_space) {
        south_space_ = south_space;
        SetValidGap(kSouthValid);
    }

    virtual void SetAround(int32_t west_space, 
                          int32_t north_space, 
                          int32_t east_space, 
                          int32_t south_space) {
        SetWestSpace(west_space);
        SetNorthSpace(north_space);
        SetEastSpace(east_space);
        SetSouthSpace(south_space);
    }

    virtual void SetValidGap(GapValid gap_valid, bool valid = true) {
        if(valid) {
            gap_valid_ |= gap_valid;
        }
        else {
            gap_valid_ &= ~gap_valid;
        }
    }

    virtual bool IsValidGap(GapValid gap_valid) const {
        return (gap_valid_ & gap_valid) == gap_valid;
    }

    /* 偏好大小 */
    virtual void SetPreferSize(int32_t width, int height) {
        prefer_size_ = Size(width, height);
    }

    virtual void SetPreferSize(const Size& size) {
        prefer_size_ = size;
    }

    virtual Size PreferSize() const {
        return prefer_size_;
    }

    virtual int32_t WestSpace() const {
        return west_space_;
    }

    virtual int32_t NorthSpace() const {
        return north_space_;
    }

    virtual int32_t EastSpace() const {
        return east_space_;
    }

    virtual int32_t SouthSpace() const {
        return south_space_;
    }

    virtual void SetCoordinate(int32_t x, int32_t y) {
        x_ = x;
        y_ = y;
    }

    virtual void SetSize(int32_t width, int32_t height) {
        size_ = Size(width, height);
    }

    virtual void SetSize(const Size& size) {
        size_ = size;
    }

    virtual void SetGeometry(int32_t x, int32_t y, int32_t width, int32_t height) {
        SetCoordinate(x, y);
        SetSize(width, height);
    }
protected:
    LayoutItem():
                west_space_(0),
                north_space_(0),
                east_space_(0),
                south_space_(0),
                gap_valid_(0),
                prefer_size_(0,0) {

    }

    //贴边留白
    int32_t west_space_;
    int32_t north_space_;
    int32_t east_space_;
    int32_t south_space_;
    int32_t gap_valid_;
    //偏好大小
    Size prefer_size_;
    //实际布局与大小
    int32_t x_;
    int32_t y_;
    Size size_;
};

#endif