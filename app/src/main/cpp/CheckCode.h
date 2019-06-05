//
// Created by Administrator on 6/5/2019.
//

#ifndef OPENCVDEMO_CHECKCODE_H
#define OPENCVDEMO_CHECKCODE_H


#include "include/opencv2/core.hpp"
#include "include/opencv2/core/mat.hpp"

using namespace cv;
using namespace std;
extern "C" {
    void Check(JNIEnv *env,Mat image,vector<Mat>& result);
}


#endif //OPENCVDEMO_CHECKCODE_H
