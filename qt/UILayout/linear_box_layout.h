#ifndef LINEAR_BOX_LAYOUT_H_
#define LINEAR_BOX_LAYOUT_H_

#include "layout.h"
#include "box_layout_item.h"

namespace ui
{
class LayoutBaseItem;  
class LinearBoxLayoutItem;  
class LayoutSpace;

class LinearBoxLayout:public Layout
{
public:
    LinearBoxLayout();
    ~LinearBoxLayout();
    
    struct AllocHelper
    {
        enum AllocStatus{
            kNoAlloc = 0,
            kTempAlloc,
            kAlloc
        };

        AllocHelper():
            section(0),
            status(kNoAlloc),
            box_item(nullptr) {

        }

        uint32_t section;
        AllocStatus status;
        LinearBoxLayoutItem* box_item;
    };

    void SetWestSpace(LayoutBaseItem *item, uint32_t west_space);
    void SetNorthSpace(LayoutBaseItem *item, uint32_t north_space);
    void SetEastSpace(LayoutBaseItem *item, uint32_t east_space);
    void SetSouthSpace(LayoutBaseItem *item, uint32_t south_space);
    void SetAround(LayoutBaseItem *item, 
        uint32_t west_space, 
        uint32_t north_space, 
        uint32_t east_space, 
        uint32_t south_space);
    void SetValidGap(LayoutBaseItem *item,
        BoxLayoutItem::GapValid gap_valid,
        bool valid = true);

    void SetStrechFactor(LayoutBaseItem* item, uint32_t strech_factor);
    void SetStrongElastic(LayoutBaseItem* item);
    void SetWeakElastic(LayoutBaseItem* item);
    
    virtual void AddWidget(Widget* widget) override ;
    virtual bool InsertWidget(uint32_t index, Widget *widget) override ;
    virtual bool RemoveWidget(Widget *widget) override ;
    
    virtual void AddLayout(Layout* layout) override ;
    virtual bool InsertLayout(uint32_t index, Layout *layout) override ;
    virtual bool RemoveLayout(Layout *layout) override ;
    
    void AddSpace(LayoutSpace* space);
    bool InsertSpace(uint32_t index, LayoutSpace *space) ;
    bool RemoveSpace(LayoutSpace *space) ;
    
    virtual bool IsEmpty();
protected:
    virtual void Relayout() override;
    virtual void ResetPreferLimitSize(bool deep = true) override;
    
    virtual bool IsUnderPrefer() = 0;
    virtual void DoUnderPrefer() = 0;
    virtual void DoExceedPrefer() = 0;
    virtual void AllocHelperToBox() = 0;

    void BoxToAllocHelper();
    bool IsStrongWeakAllInNoAlloc();
    void ResetTempAllocToNoAlloc();
    LinearBoxLayoutItem* GetLinearBoxLayoutItem(LayoutBaseItem *item);

    std::vector<AllocHelper> alloc_sections_;
};
} // namespace ui

#endif