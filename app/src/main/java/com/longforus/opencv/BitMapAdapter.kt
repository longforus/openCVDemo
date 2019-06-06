package com.longforus.opencv

import android.content.Context
import android.graphics.Bitmap
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView

/**
 * @describe
 * @author  XQ Yang
 * @date 6/5/2019  3:51 PM
 */
class BitMapAdapter(var data:List<Bitmap>,val context:Context) :RecyclerView.Adapter<ViewHolder>(){
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        return ViewHolder(LayoutInflater.from(context).inflate(R.layout.item_code,parent,false))
    }

    override fun getItemCount(): Int = data.size

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        val view = holder.itemView.findViewById<ImageView>(R.id.iv)
        view.setImageBitmap(data[position])
        val tv = holder.itemView.findViewById<TextView>(R.id.tv_code)
        val result = decodeQR(data[position])
        tv.text =  result?.toString()+result?.barcodeFormat ?: "null"
    }

}

class ViewHolder(view:View):RecyclerView.ViewHolder(view)