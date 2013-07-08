#include <QApplication>
#include <QWidget>
#include "fakes_window.h"
#include "fakes_button.h"
#include "layout_item.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    UI::Window win;
    UI::Button btn(&win);



    return app.exec();
}