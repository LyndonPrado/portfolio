package com.example.lyndon.portfolio_app_java

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.v7.recyclerview.R.attr.layoutManager
import android.support.v7.widget.LinearLayoutManager
import android.support.v7.widget.RecyclerView
import java.util.*
import android.util.Log
import kotlinx.android.synthetic.main.activity_main.*
class MainActivity : AppCompatActivity() {
    private val TAG = "RecylerViewAdapter"

    //vars
    private val mNames = ArrayList<String>()
    private val mImageUrls = ArrayList<String>()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Example of a call to a native method
        sample_text.text = stringFromJNI()
        initImage()
    }


    fun initImage() {
        Log.d(TAG,"initImageBitmaps:  preparing bitmaps.")
        mImageUrls.add("https://www.google.com/url?sa=i&source=images&cd=&ved=2ahUKEwizkO74-MfjAhVaf30KHf9UBkMQjRx6BAgBEAU&url=https%3A%2F%2Fwww.pexels.com%2Fsearch%2Fflower%2F&psig=AOvVaw1-XgHqcPQSci4ulW_o1n89&ust=1563864915053564")
        mNames.add("blue flower")
        mImageUrls.add("https://www.google.com/url?sa=i&source=images&cd=&ved=2ahUKEwj1hc6S-cfjAhWCSH0KHRVAATkQjRx6BAgBEAU&url=https%3A%2F%2Fwww.pexels.com%2Fsearch%2Fnature%2F&psig=AOvVaw1-XgHqcPQSci4ulW_o1n89&ust=1563864915053564")
        mNames.add("beach")

        initRecyclerView()
    }
    fun initRecyclerView(){
        Log.d(TAG,"initRecyclerView")
        var recyclerView: RecyclerView = findViewById<RecyclerView>(R.id.recyler_view)
        var adapter: RecylerViewAdapter = RecylerViewAdapter(this, mNames,mImageUrls)
        recyclerView.adapter = adapter
        recyclerView.layoutManager = LinearLayoutManager(this,LinearLayoutManager.VERTICAL,false)
    }
    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {

        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }
}
