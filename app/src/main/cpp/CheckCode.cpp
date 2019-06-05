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
    GaussianBlur(imageGray, imageGuussian, Size(3, 3),
                 0);
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
    blur(imageSobelOut, imageSobelOut, Size(3, 3)
    );
    LOGD("均值滤波");
//    return imageSobelOut;
////二值化
    Mat imageSobleOutThreshold;
    threshold(imageSobelOut, imageSobleOutThreshold,100, 255, CV_THRESH_BINARY);
    LOGD("二值化");

////闭运算，填充条形码间隙
    Mat element = getStructuringElement(1, Size(9, 9));
    morphologyEx(imageSobleOutThreshold, imageSobleOutThreshold, MORPH_CLOSE, element
    );
    LOGD("闭运算");
//
//腐蚀，去除孤立的点
    erode(imageSobleOutThreshold, imageSobleOutThreshold, element
    );
    LOGD("腐蚀");


//膨胀，填充条形码间空隙，根据核的大小，有可能需要2~3次膨胀操作
    dilate(imageSobleOutThreshold, imageSobleOutThreshold, element);
//    dilate(imageSobleOutThreshold, imageSobleOutThreshold, element
//    );
//    dilate(imageSobleOutThreshold, imageSobleOutThreshold, element
//    );
////dilate(imageSobleOutThreshold, imageSobleOutThreshold, element);
////dilate(imageSobleOutThreshold, imageSobleOutThreshold, element);
////dilate(imageSobleOutThreshold, imageSobleOutThreshold, element);
    LOGD("膨胀");


    vector<vector<Point>> contours;
    vector<Vec4i> hiera;

    findContours(imageSobleOutThreshold, contours, hiera, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
//    result = vector(contours.size());
    for (const auto &contour : contours) {
        Rect rect = boundingRect(contour);
        rectangle(image, rect, Scalar(255), 2);
        Mat ROI = image(rect);
        result.push_back(ROI);
    }
    LOGD("rect 完成");
}


