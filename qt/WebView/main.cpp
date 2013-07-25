#include <QApplication>
#include <QWidget>
#include <QtWebKitWidgets/QWebView>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.resize(250, 150);
    //window.setWindowTitle("Hello Qt !!!");
    
    QWebView *view = new QWebView(&window);
    view->load(QUrl("http://www.163.com"));
    view->show();
    
    QPushButton btn(&window);
    btn.setGeometry(0, 0, 500, 500);
    btn.show();
    
    window.show();

    return app.exec();
}