#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencvwidget.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_lowThresholdSlider_sliderMoved(int position);

    void on_imageProcessingCheckBox_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    openCVWidget* imageWidget;
};

#endif // MAINWINDOW_H
