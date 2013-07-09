#include <QApplication>
#include <QLayout>

#include "boxlayout.h"
#include "ywindow.h"
#include "button.h"

#include <QTimer>
#include <QObject>
#include "timer.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ui::Window win;
    win.SetGeometry(100, 100, 400, 500);
    win.Show();

    ui::Button btn;
    win.AddChild(&btn);
    btn.SetText("Mr Fan");
    btn.SetNorthSpace(10);
    btn.SetSouthSpace(10);
    btn.SetEastSpace(100);
    btn.SetWestSpace(50);
    btn.Show();

    ui::Button btn2;
    btn.AddChild(&btn2);
    btn2.SetText("Mr Fan");
    btn2.SetSouthSpace(10);
    btn2.SetWestSpace(100);
    btn2.SetEastSpace(100);
    btn2.Show();

    ui::BoxLayout layout2;
    layout2.AddItem(&btn2);
    btn.SetLayout(&layout2);

    ui::BoxLayout layout;
    layout.AddItem(&btn);
    win.SetLayout(&layout);
    
    Timer c(&win);

    QTimer *timer = new QTimer;
    QObject::connect(timer, SIGNAL(timeout()), &c, SLOT(Update()));
    timer->start(500);
    return app.exec();
}