#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    imageWidget = new openCVWidget();
    this->ui->verticalLayout->addWidget(imageWidget);
    imageWidget->startWebCam();
    this->ui->lowThresholdSlider->setRange(0,imageWidget->getLowThresholdMaxValue());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lowThresholdSlider_sliderMoved(int position)
{
    this->imageWidget->setLowThresholdValue(position);
}



void MainWindow::on_imageProcessingCheckBox_toggled(bool checked)
{
    this->imageWidget->setImageProcessing(checked);
}
