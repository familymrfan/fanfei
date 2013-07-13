#include <QApplication>
#include <QLayout>

#include "boxlayout.h"
#include "hboxlayout.h"
#include "ywindow.h"
#include "button.h"
#include "vboxlayout.h"

#include <QTimer>
#include <QObject>
#include "timer.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ui::Window win;
    win.SetGeometry(100, 100, 500, 500);
    
    /* BOX */
    /*ui::Button btn;
    win.AddChild(&btn);
    btn.SetText("outside");
   
    ui::BoxLayout layout;
    layout.AddItem(&btn);
    layout.SetEastSpace(&btn, 10);
    layout.SetNorthSpace(&btn, 10);
    layout.SetSouthSpace(&btn, 10);

    win.SetLayout(&layout);
    win.Relayout();
    
    btn.Show();*/

    ui::Button btn;
    win.AddChild(&btn);
    btn.SetText("A");

    ui::Button btn2;
    win.AddChild(&btn2);
    btn2.SetText("B");

    ui::Button btn3;
    win.AddChild(&btn3);
    btn3.SetText("C");

    ui::VBoxLayout vlayout;
    vlayout.AddItem(&btn);
    

    ui::HBoxLayout hlayout;
    hlayout.AddItem(&btn2);
    hlayout.AddItem(&btn3);

    vlayout.AddItem(&hlayout);
    win.SetLayout(&vlayout);
    win.Relayout();
    win.Show();


    /* Ä£Äâ onsize */
    Timer c(&win);
    QTimer *timer = new QTimer;
    QObject::connect(timer, SIGNAL(timeout()), &c, SLOT(Update()));
    timer->start(500);

    return app.exec();
}