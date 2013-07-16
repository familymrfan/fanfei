#ifndef WIDGET_H_
#define WIDGET_H_

#include "layout.h"

#include <QWidget>
#include <vector>
#include <QTimer>
#include <QObject>
#include <QMessageBox>

namespace ui
{

class Widget:public LayoutBaseItem
{
    typedef QWidget FakeWidget;
public:
    virtual ~Widget() {}

    virtual void AddChild(Widget* widget) {
        auto iter = children_.begin();
        while (iter != children_.end()) {
            if(*iter == widget) {
                return ;
            }
            iter++;
        }
        if(fake_widget_ != nullptr) {
            widget->GetFakeWidget()->setParent(fake_widget_);
        }
        children_.push_back(widget);
        widget->parent_ = this;
    }

    virtual void RemoveChild(Widget* widget) {
        auto iter = children_.begin();
        while (iter != children_.end()) {
            if(*iter == widget) {
                children_.erase(iter);
                break;
            }
            iter++;
        }
    }
    
    Widget* ChildAt(uint32_t index) {
        if(index < 0 || index >= ChildrenNum())
            return nullptr;
        return children_[index];
    }

    uint32_t ChildrenNum() const {
        return children_.size();
    }
    
    virtual void SetParent(Widget* widget) {
        if(fake_widget_ != nullptr) {
            fake_widget_->setParent(widget->GetFakeWidget());
        }
        widget->AddChild(this);
    }
    
    virtual void SetGeometry(int32_t x, int32_t y, uint32_t width, uint32_t height) override {
        fake_widget_->setGeometry(x, y, width, height);
        LayoutBaseItem::SetGeometry(x, y, width, height);
    }
    
    virtual void Show() {
        fake_widget_->show();
    }
    virtual void Hide() {
        fake_widget_->hide();
    }
    //Fake remove later
    FakeWidget* GetFakeWidget() {
        return fake_widget_;
    }

    void SetLayout(Layout* layout) {
        if(layer_.size() > 0) {
            layer_[0] = layout;
        } else {
            layer_.push_back(layout);
        }
    }

    virtual uint32_t Width() {
        return fake_widget_->width();
    }

    virtual uint32_t Height() {
        return fake_widget_->height();
    }

public:
    virtual void Relayout() override {
        if(layer_.size() > 0) {
            int32_t width = Width(), height = Height();
            if(Width() < layer_[0]->LimitMinWidth()) {
                width = layer_[0]->LimitMinWidth();
            }

            if(Width() > layer_[0]->LimitMaxWidth()) {
                width = layer_[0]->LimitMaxWidth();
            }

            if(Height() < layer_[0]->LimitMinHeight()) {
                height = layer_[0]->LimitMinHeight();
            }

            if(Height() > layer_[0]->LimitMaxHeight()) {
                height = layer_[0]->LimitMaxHeight();
            }
            fake_widget_->resize(width, height);
            layer_[0]->SetGeometry(0, 0, width, height);
            layer_[0]->Relayout();
        }
    }
    
protected:
    Widget()
        :parent_(nullptr),
        fake_widget_(nullptr){

    }

    std::vector<Widget*> children_;
    std::vector<Layout*> layer_;
    Widget* parent_;

    //Fake remove later
    FakeWidget *fake_widget_;
};
} // namespace ui

#endif