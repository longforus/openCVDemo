package com.longforus.opencv

import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.os.Bundle
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_main.*



class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Example of a call to a native method
        sample_text.text = stringFromJNI()
        btn_start.setOnClickListener {
            val bitmap = BitmapFactory.decodeResource(resources, R.drawable.tm2_meitu_1)
            val idArea = JniMethod.getIdArea(bitmap, Bitmap.Config.ARGB_8888)
            for (s in idArea) {
                Log.i(TAG,s ?: "null")
            }
//            rv.adapter = BitMapAdapter(idArea.toList(),this@MainActivity)
        }

    }

    val TAG = "MainActivity"

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String



    companion object {

        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("OpenCV")
        }
    }
}
