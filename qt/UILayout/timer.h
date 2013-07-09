#ifndef TIMER_H_
#define TIEMR_H_

#include "widget.h"
#include <QObject>

class Timer: public QObject
{
    Q_OBJECT
public:
    Timer(ui::Widget* widget) {
	widget_ = widget;
      
    }
  
    
    
    virtual ~Timer() {
      
    }
public slots:
    void Update() {
	widget_->Update();
    }
    
private:
    ui::Widget *widget_;
};

#endif
