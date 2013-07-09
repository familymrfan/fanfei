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
    btn.Show();

    ui::BoxLayout layout;
    layout.AddItem(&btn);
    win.SetLayout(&layout);
    
    win.Update();

    Timer c(&win);

    QTimer *timer = new QTimer;
    QObject::connect(timer, SIGNAL(timeout()), &c, SLOT(Update()));
    timer->start(500);

    return app.exec();
}