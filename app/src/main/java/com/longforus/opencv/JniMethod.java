package com.longforus.opencv;

import android.graphics.Bitmap;

/**
 * @author XQ Yang
 * @description
 * @date 2019-06-04  22:15
 */
public class JniMethod {
    public static native Bitmap getIdArea(Bitmap bitmap, Bitmap.Config config);
}
