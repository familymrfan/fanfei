#include <QApplication>

#include "ywindow.h"
#include "button.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ui::Window win;
    win.SetGeometry(100, 100, 500, 500);
    win.Show();

    ui::Button btn;
    win.AddChild(&btn);
    btn.SetGeometry(10, 10, 200, 100);
    btn.SetText("Mr Fan");
    btn.Show();

    return app.exec();
}