//
// Created by Administrator on 6/5/2019.
//


#include <opencv2/opencv.hpp>
#include <android/bitmap.h>
#include <opencv2/imgproc/types_c.h>
#include "CheckCode.h"
#include <vector>
#include "AndroidLog.h"
//检测部分  需要用到opencv开源计算机视觉库
//输入是RGB  输出是保存的检测部分


void Check(JNIEnv *env, Mat image,vector<Mat>& result) {


//原图像大小调整，提高运算效率
//resize(image, image, Size(500, 300));
//imshow("原图像", image); waitKey(15);		system("pause");


    Mat imageGray;
    Mat imageGuussian;
    Mat imageSobelX;
    Mat imageSobelY;
    Mat imageSobelOut;

//转化为灰度图
    cvtColor(image, imageGray, CV_RGB2GRAY
    );
//imshow("灰度图", imageGray); waitKey(15);		system("pause");

    LOGD("灰度图");
////高斯平滑滤波
    GaussianBlur(imageGray, imageGuussian, Size(3, 3),0);
////imshow("高斯平衡滤波", imageGuussian); waitKey(15);		system("pause");
    LOGD("高斯平衡滤波");


////求得水平和垂直方向灰度图像的梯度差,使用Sobel算子
    Mat imageX16S, imageY16S;
    Sobel(imageGuussian, imageX16S, CV_16S,
          1, 0, 3, 1, 0, 4);
    Sobel(imageGuussian, imageY16S, CV_16S,
          0, 1, 3, 1, 0, 4);
    convertScaleAbs(imageX16S, imageSobelX,
                    1, 0);
    convertScaleAbs(imageY16S, imageSobelY,
                    1, 0);
    imageSobelOut = imageSobelX - imageSobelY;
////LOGD("X方向梯度", imageSobelX); waitKey(15);		system("pause");
////LOGD("Y方向梯度", imageSobelY); waitKey(15);		system("pause");
////LOGD("XY方向梯度差", imageSobelOut); waitKey(15);		system("pause");
//
////均值滤波，消除高频噪声
    blur(imageSobelOut, imageSobelOut, Size(3, 3));
    LOGD("均值滤波");
    result.push_back(imageSobelOut);
////二值化
    Mat imageSobleOutThreshold;
    threshold(imageSobelOut, imageSobleOutThreshold,121, 255, CV_THRESH_BINARY);
    LOGD("二值化");
    result.push_back(imageSobleOutThreshold);

    Mat imagemorphologyEx;
//
//////闭运算，填充条形码间隙
    Mat element = getStructuringElement(1, Size(8,8));
    morphologyEx(imageSobleOutThreshold, imagemorphologyEx, MORPH_CLOSE, element);
    LOGD("闭运算");
    result.push_back(imagemorphologyEx);
//腐蚀，去除孤立的点
    Mat imageerode;
    erode(imagemorphologyEx, imageerode, getStructuringElement(2, Size(2,4)),Point(-1,-1),2);
    LOGD("腐蚀");
    result.push_back(imageerode);


    Mat imagedilate;
    ////膨胀，填充条形码间空隙，根据核的大小，有可能需要2~3次膨胀操作
    dilate(imageerode, imagedilate, getStructuringElement(0, Size(20,10)),Point(-1,-1),5);
    LOGD("膨胀");
    result.push_back(imagedilate);


//
//


    vector<vector<Point>> contours;
    vector<Vec4i> hiera;



    findContours(imagedilate, contours, hiera, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    for (const auto &contour : contours) {
        Rect rect = boundingRect(contour);
        if (rect.height < 150 ||(rect.height * 2.5) > rect.width){
            continue;
        }
        rectangle(image, rect, Scalar(255), 2);
        Mat ROI = image(rect);
        result.push_back(ROI);
    }
    LOGD("rect 完成");
}


