//
// Created by longforus on 2019-06-04.
//

#ifndef OPENCV_CONVERT_H
#define OPENCV_CONVERT_H

#include "include/opencv2/core.hpp"
#include "include/opencv2/core/mat.hpp"

using namespace cv;

extern "C" {
    void BitmapToMat2(JNIEnv *env,jobject& bitmap,Mat& mat , jboolean needUnPremultiplyAlpha = 0);
    void MatToBitmap2(JNIEnv *env,Mat& mat ,jobject& bitmap, jboolean needUnPremultiplyAlpha = 0);
    jobject mat_to_bitmap(JNIEnv * env, Mat & src, bool needPremultiplyAlpha, jobject bitmap_config);
}

#endif //OPENCV_CONVERT_H
