#include "mainwindow.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    int id_mat = qRegisterMetaType<cv::Mat>("cv::Mat"); //meta types for signals and slots
    int id_processType = qRegisterMetaType<processType>("processType");

    w.show();

    return a.exec();
}
