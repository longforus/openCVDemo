//
// Created by Administrator on 6/5/2019.
//


#include <android/log.h>
#ifndef OPENCVDEMO_ANDROIDLOG_H
#define OPENCVDEMO_ANDROIDLOG_H
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "error", __VA_ARGS__))
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, "debug", __VA_ARGS__))

#endif //OPENCVDEMO_ANDROIDLOG_H
