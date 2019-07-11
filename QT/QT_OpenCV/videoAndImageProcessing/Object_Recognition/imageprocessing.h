#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QRunnable>
#include <QThread>
#include <QThreadPool>
#include <opencv2/opencv.hpp>

typedef enum {
    CANNY_THRESHOLDING,
    BLUR,
    EDGE_DETECTION
}processType;

class processWorker :public QObject, public QRunnable
{
    Q_OBJECT
public:
    processWorker(const cv::Mat imageToProcess,processType typeOfWork)
    {
        this->_imageToProcess = imageToProcess;
        this->_typeOfWork = typeOfWork;
    }
signals:
    void returnImage(const cv::Mat imageToReturn,processType typeOfWork);
private:
    void run() override
    {
        qDebug() << "processing: ";
        cv::Mat toReturn;
        switch (_typeOfWork) {
        case CANNY_THRESHOLDING:
        {
            qDebug() << "CANNY_THRESHOLDING";
//            cv::Canny(_imageToProcess,toReturn,255/3,255);
            cv::threshold(_imageToProcess,toReturn,50,255,1);
            emit returnImage(toReturn,CANNY_THRESHOLDING);
            break;
        }
        case BLUR:
            qDebug() << "BLUR";
            cv::cvtColor(_imageToProcess,toReturn,CV_BGR2RGB);
            cv::blur(toReturn,toReturn,cv::Size(3,3));
            emit returnImage(toReturn,BLUR);
            break;
        case EDGE_DETECTION:
            Q_ASSERT_X(false,"run","EDGE_DETECTION not implemented yet!");
            break;
        default:
            break;
        }
    }
    cv::Mat _imageToProcess;
    processType _typeOfWork;
};

class imageProcessing : public QObject
{
    Q_OBJECT
public:
    explicit imageProcessing(QObject* parent = 0):QObject(parent)
    {

    }

    void thresholdedImage(cv::Mat raw, double thresholdVal){
        processWorker* blurProcess = new processWorker(raw,BLUR);
        connect(blurProcess,
                SIGNAL(returnImage(cv::Mat,processType)),
                this,
                SLOT(nextProcess(cv::Mat,processType)));
        QThreadPool::globalInstance()->start(blurProcess);
    }

public slots:
    void nextProcess(const cv::Mat image, processType previousWork)
    {
        switch (previousWork) {
        case CANNY_THRESHOLDING:
        {
            Q_ASSERT_X(false,"nextProcess","CANNY_THRESHOLDING not implemented yet!");

            break;
        }
        case BLUR:
            startCannyProcess(image);
            break;
        case EDGE_DETECTION:
            Q_ASSERT_X(false,"nextProcess","EDGE_DETECTION not implemented yet!");
            break;
        default:
            break;
        }
    }

    void startCannyProcess(const cv::Mat blurImage)
    {
        processWorker* cannyProcess = new processWorker(blurImage,CANNY_THRESHOLDING);
        connect(cannyProcess,SIGNAL(returnImage(cv::Mat,processType)),this,SIGNAL(returnImage(cv::Mat,processType)));
        QThreadPool::globalInstance()->start(cannyProcess);
    }


signals:
    void returnImage(const cv::Mat imageToReturn,processType workDone);
private:
    int const max_BINARY_value = 255;
    int const threshold_type = 3;


};



#endif // IMAGEPROCESSING_H
