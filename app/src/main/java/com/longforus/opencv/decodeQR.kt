package com.longforus.opencv

import android.graphics.Bitmap
import com.google.zxing.BinaryBitmap
import com.google.zxing.MultiFormatReader
import com.google.zxing.RGBLuminanceSource
import com.google.zxing.common.GlobalHistogramBinarizer

/**
     * 解析二维码图片
     *
     * @param srcBitmap
     * @return
     */
    fun decodeQR(srcBitmap: Bitmap?): com.google.zxing.Result? {
        var result: com.google.zxing.Result? = null
        if (srcBitmap != null) {
            val width = srcBitmap.width
            val height = srcBitmap.height
            val pixels = IntArray(width * height)
            srcBitmap.getPixels(pixels, 0, width, 0, 0, width, height)
            // 新建一个RGBLuminanceSource对象
            val source = RGBLuminanceSource(width, height, pixels)
            // 将图片转换成二进制图片
            val binaryBitmap = BinaryBitmap(GlobalHistogramBinarizer(source))
            val reader = MultiFormatReader()// 初始化解析对象
            try {
                result = reader.decode(binaryBitmap,CodeHints.getCustomDecodeHints(""))// 开始解析
            } catch (e: Exception) {
                e.printStackTrace()
            }

        }
        return result
    }