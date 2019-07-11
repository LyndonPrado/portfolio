#include "mainwindow.h"
#include <QApplication>
#include <opencvwidget.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    int id_mat = qRegisterMetaType<cv::Mat>("cv::Mat"); //meta types for signals and slots
    int id_processType = qRegisterMetaType<processType>("processType");
    openCVWidget* imageWidget = new openCVWidget();
    w.setCentralWidget(imageWidget);
    imageWidget->startWebCam();
    w.show();

    return a.exec();
}
