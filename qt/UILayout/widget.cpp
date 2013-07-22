#include "widget.h"
#include <QWidget>
#include <QTimer>
#include <QObject>
#include <QMessageBox>
#include <vector>
#include "layout.h"

namespace ui
{
Widget::Widget():parent_(nullptr),
        fake_widget_(nullptr){

}

Widget::~Widget() {

}

void Widget::AddChild(Widget* widget) {
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

void Widget::RemoveChild(Widget* widget) {
    widget->SetParent(nullptr);
    auto iter = children_.begin();
    while (iter != children_.end()) {
	if(*iter == widget) {
	    children_.erase(iter);
	    break;
	}
	iter++;
    }
}

Widget* Widget::ChildAt(uint32_t index) {
    if(index < 0 || index >= ChildrenNum())
	return nullptr;
    return children_[index];
}

uint32_t Widget::ChildrenNum() const {
    return children_.size();
}

void Widget::SetParent(Widget* widget) {
    if(fake_widget_ != nullptr) {
      if(widget) {
	fake_widget_->setParent(widget->GetFakeWidget());
	widget->AddChild(this);
      } else {
	fake_widget_->setParent(nullptr);
      }
    }
}

Widget* Widget::Parent() const {
    return parent_;
}

void Widget::SetGeometry(int32_t x, int32_t y, uint32_t width, uint32_t height) {
    fake_widget_->setGeometry(x, y, width, height);
    LayoutBaseItem::SetGeometry(x, y, width, height);
}

void Widget::Show() {
    fake_widget_->show();
}

void Widget::Hide() {
    fake_widget_->hide();
}

bool Widget::IsVisible() const{
    return fake_widget_->isVisible();
}

//Fake remove later
Widget::FakeWidget* Widget::GetFakeWidget() {
    return fake_widget_;
}

void Widget::SetLayout(Layout* layout) {
    if(layer_.size() > 0) {
	layer_[0] = layout;
    } else {
	layer_.push_back(layout);
    }
    layout->SetParentWidget(this);
}

uint32_t Widget::Width() {
    return fake_widget_->width();
}

uint32_t Widget::Height() {
    return fake_widget_->height();
}

void Widget::ResetPreferLimitSize() {
    if(layer_.size() > 0 && layer_[0]) {
      layer_[0]->ResetPreferLimitSize();
      
      SetPreferWidth(layer_[0]->PreferWidth());
      SetPreferHeight(layer_[0]->PreferHeight());
      SetLimitMinWidth(layer_[0]->LimitMinWidth());
      SetLimitMinHeight(layer_[0]->LimitMinHeight());
      SetLimitMaxWidth(layer_[0]->LimitMaxWidth());
      SetLimitMaxHeight(layer_[0]->LimitMaxHeight());
    }
}

void Widget::Relayout() {
    if(layer_.size() > 0) {
	if(parent_ == nullptr) {
	  ResetPreferLimitSize();
	}
	layer_[0]->SetGeometry(0, 0, Width(), Height());
	layer_[0]->Relayout();
    }
}
} // namespace ui