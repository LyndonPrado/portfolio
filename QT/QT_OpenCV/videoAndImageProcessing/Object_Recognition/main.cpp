#include "mainwindow.h"
#include <QApplication>
#include <opencvwidget.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    openCVWidget* imageWidget = new openCVWidget();
    w.setCentralWidget(imageWidget);
    imageWidget->startWebCam();
    w.show();

    return a.exec();
}
