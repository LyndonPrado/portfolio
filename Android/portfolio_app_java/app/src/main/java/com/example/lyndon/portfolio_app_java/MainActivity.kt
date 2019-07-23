package com.example.lyndon.portfolio_app_java

import android.net.Uri
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.v7.recyclerview.R.attr.layoutManager
import android.support.v7.widget.LinearLayoutManager
import android.support.v7.widget.RecyclerView
import java.util.*
import android.util.Log
import android.widget.VideoView
import kotlinx.android.synthetic.main.activity_main.*
import kotlinx.android.synthetic.main.video_background.*

class MainActivity : AppCompatActivity() {
    private val TAG = "RecylerViewAdapter"
    private final val VIDEO_BACKGROUND:String = "background_video"

    //vars
    private val mNames = ArrayList<String>()
    private val mImageIds = ArrayList<Int>()
    private val mImageText = ArrayList<String>()
    private lateinit var mbackgroundVid:VideoView
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Example of a call to a native method
        sample_text.text = stringFromJNI()
        initImage()
        initBackgroundVideo()
    }

    fun initBackgroundVideo(){
        Log.d(TAG,"initBackgroundVideo")

        mbackgroundVid = findViewById<VideoView>(R.id.video_view)
        var videoUri:Uri = getMedia(VIDEO_BACKGROUND)
        mbackgroundVid.setVideoURI(videoUri)
        mbackgroundVid.holder.setSizeFromLayout();
        mbackgroundVid.start()
    }

    fun getMedia(arg: String): Uri {
        return Uri.parse("android.resource://" + packageName + "/raw/" + arg)
    }
    fun initImage() {
        Log.d(TAG,"initImageBitmaps:  preparing bitmaps.")
        mImageIds.add(R.drawable.profile_picture);
        mNames.add("Lyndon Prado")
        mImageText.add("Hello Guys! This is my portfolio application, displaying my basic skills in developing an" +
                " android application.");
        mImageIds.add(R.drawable.about_me_picture);
        mNames.add("About Me")
        mImageText.add("Im still in the process of gaining more skills in the area of Android Development. This is because" +
                " my main area of focus is in IoT development, with having most of my experience in developing embedded " +
                " applications and desktop applications in the C++ programming language. I am very adaptable and should be " +
                " able to pick up any technology given some time. I am language agnostic, so I can easily pick up any programming" +
                " language to learn ")


        initRecyclerView()
    }
    fun initRecyclerView(){
        Log.d(TAG,"initRecyclerView")
        var recyclerView: RecyclerView = findViewById<RecyclerView>(R.id.recyler_view)
        var adapter: RecylerViewAdapter = RecylerViewAdapter(this, mNames,mImageIds,mImageText)
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
