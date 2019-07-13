#ifndef OPENCVWIDGET_H
#define OPENCVWIDGET_H

#include <iostream>
#include <functional>
#include <thread>
#include <QObject>
#include <QThread>
#include <QTimer>
#include <qDebug>
#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QMutex>
#include <QMutexLocker>
#include <opencv2/opencv.hpp>


//custom libraries
#include <imageprocessing.h>


inline void threshold(cv::Mat &mat)
{
    QMutex mutex;
    mutex.lock();
    cv::blur(mat,mat,cv::Size(3,3));
    cv::threshold(mat,mat,50,255,1);
    mutex.unlock();
}

class openCVWidget : public QWidget
{
    Q_OBJECT
public:
    explicit openCVWidget(QWidget *parent = 0) : QWidget(parent)
    {
        connect(this,SIGNAL(image_ready(QImage)),this,SLOT(set_image(QImage)));
    }
    ~openCVWidget(){
    }

    QSize sizeHint() const {return imageToDraw.size();}
    QSize minimumSizeHint() const {return imageToDraw.size();}

signals:
    void image_ready(const QImage& img);
public slots:
    void set_image(const QImage& img)
    {
        imageToDraw = img;
    }
    void set_image(const cv::Mat& img)
    {
        imageToDraw = QImage(img.data, img.cols,img.rows,img.cols*3,QImage::Format_RGB888);
    }

    void showImage(const cv::Mat& image){
        switch (image.type()) {
        case CV_8UC1:
            cv::cvtColor(image,matBuffer,CV_GRAY2RGB);
            break;
        case CV_8UC3:
            cv::cvtColor(image,matBuffer,CV_BGR2RGB);
        default:
            break;
        }
        assert(matBuffer.isContinuous());
        imageToDraw = QImage(matBuffer.data, matBuffer.cols,matBuffer.rows,matBuffer.cols*3,QImage::Format_RGB888);
        this->setFixedSize(image.cols,image.rows);
        repaint();
    }

    void startWebCam() {
        const int imagePeriod = 1;
        imageTimer = new QTimer(this);
        imageTimer->setInterval(imagePeriod);
        connect(imageTimer,SIGNAL(timeout()),this,SLOT(showWebCam()));
        imageTimer->start();
    }

    void showWebCam() {
        if(cap == nullptr)
        {
            cap = new cv::VideoCapture(0);
        }
        if(!cap->isOpened())
            return;
        int i = 0;
        qDebug() << "reading camera!" << i++;
        cv::Mat frame;
        if(!cap->read(frame))
        {
            return;
        }
        cv::cvtColor(frame,matBuffer,CV_BGR2RGB);
        assert(matBuffer.isContinuous());
        //let thresholding work happen in another thread
        imageProcessing::thresholdImage(matBuffer);
        emit image_ready(QImage(matBuffer.data, matBuffer.cols,matBuffer.rows,matBuffer.cols*3,QImage::Format_RGB888));
        this->setFixedSize(frame.cols,frame.rows);
        repaint();
        if(cv::waitKey(1) >= 0) return;
    }
protected:
    void paintEvent(QPaintEvent* /*event*/){
        //Display the image
        QPainter painter(this);
        painter.drawImage(QPoint(0,0), imageToDraw);
        painter.end();
    }



    QImage imageToDraw;
    cv::Mat matBuffer;
    QTimer* imageTimer;
    cv::VideoCapture* cap = nullptr;
    bool init = false;
};

#endif // OPENCVWIDGET_H
