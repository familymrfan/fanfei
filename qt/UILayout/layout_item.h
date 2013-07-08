#ifndef LAYOUT_ITEM_H_
#define LAYOUT_ITEM_H_

#include <stdint.h>

class LayoutItem
{
public:
    enum GapValid {
        kXValid = 1,
        kYValid = 2,
        kRevXValid = 4,
        kRevYValid = 8
    };

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

    /* Ìù±ßÁô°× */
    virtual void SetX(int32_t x) {
        x_ = x;
        SetValidGap(kXValid);
    }

    virtual void SetY(int32_t y) {
        y_ = y;
        SetValidGap(kYValid);
    }

    virtual void SetRevX(int32_t rev_x) {
        rev_x_ = rev_x;
        SetValidGap(kRevXValid);
    }

    virtual void SetRevY(int32_t rev_y) {
        rev_y_ = rev_y;
        SetValidGap(kRevYValid);
    }

    virtual void SetGeometry(int32_t x, int32_t y, int32_t rev_x, int32_t rev_y) {
        SetX(x);
        SetY(y);
        SetRevX(rev_x);
        SetRevY(rev_y);
    }

    virtual void SetValidGap(GapValid gap_valid, bool valid = true) {
        if(valid) {
            gap_valid_ |= gap_valid;
        }
        else {
            gap_valid_ &= ~gap_valid;
        }
    }

    bool IsValidGap(GapValid gap_valid) const{
        return (gap_valid_ & gap_valid) == gap_valid;
    }

    /* Æ«ºÃ´óÐ¡ */
    virtual Size GetPreferSize() const {
        return Size(0, 0);
    }
protected:
    LayoutItem():
                x_(0),
                y_(0), 
                rev_x_(0), 
                rev_y_(0),
                gap_valid_(0) {

    }
    //Ìù±ßÁô°×
    int32_t x_;
    int32_t y_;
    int32_t rev_x_;
    int32_t rev_y_;
    int32_t gap_valid_;
};

#endif