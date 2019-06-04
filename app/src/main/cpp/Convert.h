//
// Created by longforus on 2019-06-04.
//

#ifndef OPENCV_CONVERT_H
#define OPENCV_CONVERT_H

#include "../../../../../../../Library/Android/sdk/ndk-bundle/toolchains/llvm/prebuilt/darwin-x86_64/sysroot/usr/include/jni.h"
#include "include/opencv2/core.hpp"
#include "include/opencv2/core/mat.hpp"

using namespace cv;

extern "C" {
    void BitmapToMat2(JNIEnv *env,jobject& bitmap,Mat& mat , jboolean needUnPremultiplyAlpha = 0);
    void MatToBitmap2(JNIEnv *env,Mat& mat ,jobject& bitmap, jboolean needUnPremultiplyAlpha = 0);
}

#endif //OPENCV_CONVERT_H
