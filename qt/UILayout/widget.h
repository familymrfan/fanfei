#ifndef WIDGET_H_
#define WIDGET_H_

#include "layout_item.h"
#include "layout.h"

#include <QWidget>
#include <vector>
#include <QTimer>
#include <QObject>
#include <QMessageBox>

namespace ui
{

class Widget:public LayoutItem
{
    typedef QWidget FakeWidget;
public:
    virtual ~Widget() {}

    virtual void AddChild(Widget* widget) {
        RemoveChild(widget);
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
    
    Widget* ChildAt(int32_t index) {
        if(index < 0 || index >= ChildrenNum())
            return nullptr;
        return children_[index];
    }

    int32_t ChildrenNum() const {
        return (int32_t)children_.size();
    }
    
    virtual void SetParent(Widget* widget) {
        if(fake_widget_ != nullptr) {
            fake_widget_->setParent(widget->GetFakeWidget());
        }
        widget->AddChild(this);
    }
    
    virtual void SetGeometry(int32_t x, int32_t y, int32_t width, int32_t height) {
        fake_widget_->setGeometry(x, y, width, height);
        LayoutItem::SetGeometry(x, y, width, height);
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

    virtual int32_t Width() const {
        return fake_widget_->width();
    }

    virtual int32_t Height() const {
        return fake_widget_->height();
    }

    virtual Size LimitedMinSize() const override {
        if(layer_.size() > 0) {
            return layer_[0]->LimitedMinSize();
        }
        return LayoutItem::LimitedMinSize();
    }

    virtual Size LimitedMaxSize() const override {
        if(layer_.size() > 0) {
            return layer_[0]->LimitedMaxSize();
        }
        return LayoutItem::LimitedMaxSize();
    }
public:
    virtual void Update() override {
        if(layer_.size() > 0) {
            int32_t width = Width(), height = Height();
            if(Width() < layer_[0]->LimitedMinSize().width_) {
                width = layer_[0]->LimitedMinSize().width_;
            }

            if(Height() > layer_[0]->LimitedMaxSize().height_) {
                height = layer_[0]->LimitedMaxSize().height_;
            }
            fake_widget_->resize(width, height);
            layer_[0]->SetGeometry(0, 0, width, height);
            layer_[0]->Update();
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
} // namespace UI

#endif