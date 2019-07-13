#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QObject>
#include <thread>
#include <functional>
#include <iostream>
#include <QDebug>
#include <QMutex>
#include <QThread>
#include <QRunnable>
#include <QThread>
#include <QThreadPool>
#include <opencv2/opencv.hpp>

inline void convert_colour(cv::Mat &inputMat, cv::Mat &outputMat,int code)
{
    cv::cvtColor(inputMat,outputMat,code);
}

inline void blur(cv::Mat &inputMat, cv::Mat &outputMat, int row_size, int columns_size)
{
    cv::blur(inputMat,outputMat,cv::Size(row_size,columns_size));
}

inline void canny(cv::Mat &inputMat,cv::Mat &outputMat,double threshold1, double threshold2)
{
    cv::Canny(inputMat,outputMat,threshold1,threshold2);
}

typedef enum {
    CANNY_THRESHOLDING,
    BLUR,
    EDGE_DETECTION
}processType;

class processWorker: public QObject
{
    Q_OBJECT
public:
    explicit processWorker(QObject* parent = 0):QObject(parent)
    {
    }

    void run(cv::Mat &imageToProcess,processType typeOfWork)
    {
        QMutex mutex;
        mutex.lock();
        qDebug() << "processing: ";
        switch (typeOfWork) {
        case CANNY_THRESHOLDING:
        {
            cv::Mat src,src_gray;
            cv::Mat dst,detected_edges;
            dst.create(imageToProcess.size(),imageToProcess.type());
            imageToProcess.copyTo(src);
            qDebug() << "CANNY_THRESHOLDING";
            std::thread thread_cvt_col(convert_colour,std::ref(src),std::ref(src_gray),CV_BGR2GRAY);
            thread_cvt_col.join();
            std::thread thread_blur(blur,std::ref(src_gray),std::ref(detected_edges),3,3);
            thread_blur.join();
            std::thread thread_canny(canny,std::ref(detected_edges),std::ref(detected_edges),lowThreshold,lowThreshold*ratio);
            thread_canny.join();
            dst = cv::Scalar::all(0);
            imageToProcess.copyTo(dst,detected_edges);
            dst.copyTo(imageToProcess);
            break;
        }
        case BLUR:
            qDebug() << "BLUR";
            cv::blur(imageToProcess,imageToProcess,cv::Size(9,9));
            break;
        case EDGE_DETECTION:
            Q_ASSERT_X(false,"run","EDGE_DETECTION not implemented yet!");
            break;
        default:
            break;
        }
        mutex.unlock();
    }



    int getLowThresholdMax() const
    {
        return lowThresholdMax;
    }

public slots:
    void setLowThreshold(int lowThreshold)
    {
        Q_ASSERT_X(lowThreshold >= 0 && lowThreshold <= lowThresholdMax,"setLowThreshold","threshold out of range!");
        this->lowThreshold = lowThreshold;
    }

private:
    int const lowThresholdMax = 100;
    int lowThreshold = 50;
    int ratio = 3;
};

class imageProcessing: public QObject
{
    Q_OBJECT
public:
    explicit imageProcessing(QObject* parent = 0):QObject(parent)
    {
        worker = new processWorker(this);
        connect(this,SIGNAL(setLowThreshold(int)),worker,SLOT(setLowThreshold(int)));
    }

    void thresholdImage(cv::Mat &raw){
        std::thread thread_threshold (processWorker::run,worker,std::ref(raw),CANNY_THRESHOLDING);
        thread_threshold.join();
    }

    int getLowThresholdMax(){return this->worker->getLowThresholdMax();}
signals:
    void setLowThreshold(int lowThreshold);
private:
    processWorker* worker;
};



#endif // IMAGEPROCESSING_H
