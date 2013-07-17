#include <QApplication>
#include <QLayout>

#include "box_layout.h"
#include "hboxlayout.h"
#include "ywindow.h"
#include "button.h"
#include "vboxlayout.h"
#include "layout_space.h"

#include <QImage>
#include <QTimer>
#include <QObject>
#include "timer.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ui::Window win;
    win.SetGeometry(100, 100, 500, 500);
    
    ui::HBoxLayout hbox;
    win.SetLayout(&hbox);
    
    ui::Button btn1,btn2,btn3,btn4;
    hbox.AddWidget(&btn1);
    hbox.AddWidget(&btn2);
    
    
    ui::VBoxLayout vbox;
    hbox.AddLayout(&vbox);
    vbox.AddWidget(&btn3);
    vbox.AddWidget(&btn4);
    
    win.Relayout();
    win.Show();

    /* Ä£Äâ onsize */
    Timer c(&win);
    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), &c, SLOT(Update()));
    timer->start(500);

    return app.exec();
}