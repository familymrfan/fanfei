#ifndef LAYOUT_ITEM_LIMITED_SIZE_H_
#define LAYOUT_ITEM_LIMITED_SIZE_H_

namespace ui
{
class LayoutItemLimitedSize
{
public:
    enum LimitedSizeStatus {
        kNormal = 0,
        kHMin = 1,
        kVMin = 2,
        kHMax = kHMin + 4,
        kVMax = kVMin + 4
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

    virtual void SetLimitedMinSize(const Size& size) {
        limited_min_size_ = size;
    }

    virtual Size LimitedMinSize() const {
        return limited_min_size_;
    }

    virtual void SetLimitedMaxSize(const Size& size) {
        limited_max_size_ = size;
    }

    virtual Size LimitedMaxSize() const {
        return limited_max_size_;
    }

    virtual void SetLimitedStatus(LimitedSizeStatus status, bool valid = true) {
        if(valid) {
            limited_status_ &= ~4;
            limited_status_ |= status;
        }
        else {
            limited_status_ &= ~status;
        }
    }

    virtual bool IsValidLimitedStatus(LimitedSizeStatus status) const {
        return (limited_status_ & status) == status && (limited_status_ & 4) == (status & 4);
    }

    bool LessThanPreferWidth(const int32_t width) const {
        if(width < PreferSize().width_) {
            return true;
        }
        return false;
    }

    bool LessThanPreferHeight(const int32_t height) const {
        if(height < PreferSize().height_) {
            return true;
        }
        return false;
    }

    bool LessThanLimitMinWidth(const int32_t width) const {
        if(width < LimitedMinSize().width_) {
            return true;
        }
        return false;
    }

    bool MoreThanLimitMaxWidth(const int32_t width) const {
        if(width > LimitedMaxSize().width_) {
            return true;
        }
        return false;
    }

    bool LessThanLimitMinHeight(const int32_t height) const {
        if(height < LimitedMinSize().height_) {
            return true;
        }
        return false;
    }

    bool MoreThanLimitMaxHeight(const int32_t height) const {
        if(height > LimitedMaxSize().height_) {
            return true;
        }
        return false;
    }
protected:
    LayoutItemLimitedSize():prefer_size_(0, 0),
                           limited_min_size_(0, 0),
                           limited_max_size_(INT32_MAX, INT32_MAX),
                           limited_status_(kNormal) {
 
    }

    //偏好大小
    Size prefer_size_;
    //最大最小约束
    Size limited_min_size_;
    Size limited_max_size_;
    //最大最小状态
    int32_t limited_status_;
};
} // namespace ui
#endif