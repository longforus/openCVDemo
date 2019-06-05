#include <jni.h>
#include <string>
#include "include/opencv2/opencv.hpp"
#include "include/opencv2/core.hpp"
#include "Convert.h"
#include "CheckCode.h"

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
JNIEXPORT jobjectArray JNICALL
Java_com_longforus_opencv_JniMethod_getIdArea(JNIEnv *env, jclass type, jobject bitmap, jobject config) {

    Mat src_image;
    jobjectArray result_arr;
    vector<Mat> result;
    // 获取类对象
    jclass cls = env->FindClass("android/graphics/Bitmap");
    BitmapToMat2(env, bitmap, src_image, false);
    Check(env, src_image,result);
    int size = result.size();
    result_arr = (jobjectArray) env->NewObjectArray(size, cls, NULL);

    for (int i = 0; i < size; ++i) {
        env->SetObjectArrayElement(result_arr,
                                   i, (jobject) mat_to_bitmap(env, result[i], false, config));
    }

    return result_arr;


}
