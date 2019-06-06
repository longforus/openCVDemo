#include <jni.h>
#include <string>
#include <opencv2/imgproc/types_c.h>
#include "include/opencv2/opencv.hpp"
#include "include/opencv2/core.hpp"
#include "Convert.h"
#include "CheckCode.h"
#include "include/zbar.h"
#include "AndroidLog.h"
using namespace std;
using namespace cv;
using namespace zbar;
extern "C" JNIEXPORT jstring JNICALL
Java_com_longforus_opencv_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_longforus_opencv_JniMethod_getIdArea(JNIEnv *env, jclass type, jobject bitmap, jobject config) {

    Mat src_image;

    jobjectArray result_arr;
    jobjectArray result_data;
    vector<Mat> result;
    // 获取类对象
    jclass cls = env->FindClass("android/graphics/Bitmap");
    jclass clsstr = env->FindClass("java/lang/String");
    BitmapToMat2(env, bitmap, src_image, false);
    Check(env, src_image,result);
    int size = result.size();
    result_arr = (jobjectArray) env->NewObjectArray(size, cls, NULL);
    result_data = (jobjectArray) env->NewObjectArray(size, clsstr, NULL);
    ImageScanner scanner;
    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

    for (int i = 0; i < size; ++i) {
//        env->SetObjectArrayElement(result_arr,
//                                   i, (jobject) mat_to_bitmap(env, result[i], false, config));

        Mat imageGray  =result[i];
//        IplImage *r = cvCreateImage(cvGetSize(temp),temp->depth,1);
//        IplImage *g = cvCreateImage(cvGetSize(temp),temp->depth,1);
//        IplImage *b = cvCreateImage(cvGetSize(temp),temp->depth,1);
//        cvSplit(temp,r,g,b,NULL);

//    cvtColor(temp, imageGray, CV_RGB2GRAY);
        //imshow("灰度图", imageGray);
        // 获取所摄取图像的长和宽
        int width = imageGray.cols;
        int height = imageGray.rows;
        // 在Zbar中进行扫描时候，需要将OpenCV中的Mat类型转换为（uchar *）类型，raw中存放的是图像的地址；对应的图像需要转成Zbar中对应的图像zbar::Image
        uchar *raw = (uchar *)imageGray.data;
        Image imageZbar(width, height, "Y800", raw, width * height);
        // 扫描相应的图像imageZbar(imageZbar是zbar::Image类型，存储着读入的图像)
        scanner.scan(imageZbar); //扫描条码
        Image::SymbolIterator symbol = imageZbar.symbol_begin();
        if ( symbol == imageZbar.symbol_end())
        {
            LOGE("查询条码失败，请检查图片！");
            //system(delFile);
            continue;
        }

        for (; symbol != imageZbar.symbol_end(); ++symbol)
        {
            std::string  type = symbol->get_type_name();
            std::string  data = symbol->get_data();
//            String str = data;
            jstring value = env->NewStringUTF(data.c_str());
//        LOGD(data.c_str());
            env->SetObjectArrayElement(result_data,
                                       i, value);
        }
    }



    return result_data;


}
