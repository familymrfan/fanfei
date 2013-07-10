#ifndef LAYOUT_ITEM_CAPACITY_ALLOC_H_
#define LAYOUT_ITEM_CAPACITY_ALLOC_H_

namespace ui
{
class LayoutItemCapacityAlloc
{
public:
    virtual void SetStrechFactor(int32_t strech_factor) {
        strech_factor_ = strech_factor;
    }

    virtual int32_t StrechFactor() const {
        return strech_factor_;
    }

    virtual void SetStrongElastic(bool strong_elastic) {
        strong_elastic_ = strong_elastic;
    }

    virtual bool IsStrongElastic() const {
        return strong_elastic_;
    }
protected:
    LayoutItemCapacityAlloc():strech_factor_(0),
                              strong_elastic_(false) {

    }

    int32_t strech_factor_;
    bool    strong_elastic_;
};
} // namespace ui
#endif