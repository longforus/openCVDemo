package com.longforus.opencv

import android.content.Context
import android.graphics.Bitmap
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import androidx.recyclerview.widget.RecyclerView

/**
 * @describe
 * @author  XQ Yang
 * @date 6/5/2019  3:51 PM
 */
class BitMapAdapter(var data:List<Bitmap>,val context:Context) :RecyclerView.Adapter<ViewHolder>(){
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        var iv = ImageView(context)
        iv.layoutParams = ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT,ViewGroup.LayoutParams.MATCH_PARENT)
        return ViewHolder(iv)
    }

    override fun getItemCount(): Int = data.size

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        val view = holder.itemView as ImageView
        view.setImageBitmap(data[position])
    }

}

class ViewHolder(view:View):RecyclerView.ViewHolder(view)