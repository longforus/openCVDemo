#include <jni.h>
#include <string>
#include "include/opencv2/opencv.hpp"
#include "include/opencv2/core.hpp"
#include "Convert.h"
using namespace std;
using namespace cv;
extern "C" JNIEXPORT jstring JNICALL
Java_com_longforus_opencv_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT jobject JNICALL
Java_com_longforus_opencv_JniMethod_getIdArea(JNIEnv *env, jclass type, jobject bitmap, jobject config) {

    Mat src_image;
    BitmapToMat2(env,bitmap,src_image, false);
    MatToBitmap2(env,src_image,bitmap,false);
    return bitmap;

}