#ifndef LAYOUT_ITEM_SIDE_SPACE_H_
#define LAYOUT_ITEM_SIDE_SPACE_H_

namespace ui
{
class LayoutItemSideSpace
{
public:
    enum GapValid {
        kWestValid =  1,
        kNorthValid = 2,
        kEastValid =  4,
        kSouthValid = 8
    };

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
protected:
    LayoutItemSideSpace():
                        west_space_(0),
                        north_space_(0),
                        east_space_(0),
                        south_space_(0),
                        gap_valid_(0) {

    }

    //Ìù±ßÁô°×
    int32_t west_space_;
    int32_t north_space_;
    int32_t east_space_;
    int32_t south_space_;
    int32_t gap_valid_;
};
} // namespace ui
#endif