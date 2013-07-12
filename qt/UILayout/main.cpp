#include <QApplication>
#include <QLayout>

#include "boxlayout.h"
#include "hboxlayout.h"
#include "ywindow.h"
#include "button.h"

#include <QTimer>
#include <QObject>
#include "timer.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ui::Window win;
    win.SetGeometry(100, 100, 800, 500);
    
    /* BOX 
    ui::Button btn;
    win.AddChild(&btn);
    btn.SetText("outside");
    btn.SetNorthSpace(0);
    btn.SetSouthSpace(0);
    btn.SetWestSpace(0);
    btn.SetEastSpace(0);

    ui::Button btn2;
    btn.AddChild(&btn2);
    btn2.SetText("inside");
    btn2.SetNorthSpace(0);
    btn2.SetSouthSpace(200);
    btn2.SetWestSpace(0);
    btn2.SetEastSpace(200);
    
    ui::Button btn3;
    btn2.AddChild(&btn3);
    btn3.SetText("inside inside");

    ui::BoxLayout layout;
    layout.AddItem(&btn);
    ui::BoxLayout layout2;
    layout2.AddItem(&btn2);
    btn.SetLayout(&layout2);
    ui::BoxLayout layout3;
    layout3.AddItem(&btn3);
    btn2.SetLayout(&layout3);

    win.SetLayout(&layout);
    win.Update();
    
    btn3.Show();
    btn2.Show();
    btn.Show();*/

    /* HBOX */
    ui::Button btn;
    win.AddChild(&btn);
    btn.SetStrechFactor(1);
    btn.SetText("A");

    ui::Button btn2;
    win.AddChild(&btn2);
    btn2.SetStrechFactor(1);
    btn2.SetText("B");

    ui::HBoxLayout layout;
    layout.AddItem(&btn);
    layout.AddItem(&btn2);
    
    win.SetLayout(&layout);
    win.Update();

    win.Show();


    /* Ä£Äâ onsize */
    Timer c(&win);
    QTimer *timer = new QTimer;
    QObject::connect(timer, SIGNAL(timeout()), &c, SLOT(Update()));
    timer->start(500);

    return app.exec();
}