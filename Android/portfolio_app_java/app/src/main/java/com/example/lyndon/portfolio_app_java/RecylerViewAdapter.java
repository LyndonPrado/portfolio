package com.example.lyndon.portfolio_app_java;

import android.app.Activity;
import android.content.Context;
import android.graphics.drawable.Drawable;
import android.os.Build;
import android.support.annotation.NonNull;
import android.support.annotation.RequiresApi;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;
import com.mikhaellopez.circularimageview.CircularImageView;

import java.util.ArrayList;

public class RecylerViewAdapter extends RecyclerView.Adapter<RecylerViewAdapter.ViewHolder> {
    private static final String TAG = "RecylerViewAdapter";

    private ArrayList<String> mImageNames = new ArrayList<>();
    private ArrayList<Integer> mImagesId = new ArrayList<>();
    private ArrayList<String> mText = new ArrayList<>();
    private Context mContext;

    public RecylerViewAdapter(Context mContext, ArrayList<String> mImageNames, ArrayList<Integer> mImagesId, ArrayList<String> mText) {
        this.mImageNames = mImageNames;
        this.mImagesId = mImagesId;
        this.mText = mText;
        this.mContext = mContext;
    }

    @NonNull
    @Override
    public ViewHolder onCreateViewHolder(@NonNull ViewGroup viewGroup, int i) {
        View view = LayoutInflater.from(viewGroup.getContext()).inflate(R.layout.layout_listitem,viewGroup,false);
        ViewHolder holder = new ViewHolder(view);
        return holder;
    }

    @RequiresApi(api = Build.VERSION_CODES.LOLLIPOP)
    @Override
    public void onBindViewHolder(@NonNull ViewHolder viewHolder, final int i) {
        Log.d(TAG,"onBindViewHolder: called.");
//        Glide.with(mContext)
//                .asBitmap()
//                .load(mImages.get(i))
//                .into(viewHolder.section_picture);
//        CircularImageView view = (CircularImageView)((Activity)this.mContext).findViewById(R.id.Section_Picture);
//        CircularImageView view = (CircularImageView)((Activity)this.mContext).findViewById(this.mImagesId.get(i));
        Drawable d = mContext.getResources().getDrawable(this.mImagesId.get(i));
        viewHolder.section_picture.setImageDrawable(d);
        viewHolder.section_title.setText(mImageNames.get(i));
        viewHolder.section_text.setText(mText.get(i));
        viewHolder.parentLayout.setOnClickListener(new View.OnClickListener(){
               @Override
               public void onClick(View view) {
                   Log.d(TAG,"onClick: clicked on: " + mImageNames.get(i));
                   Toast.makeText(mContext,mImageNames.get(i),Toast.LENGTH_SHORT).show();
               }
           }
        );
    }

    @Override
    public int getItemCount() {
        return mImageNames.size();
    }

    public class ViewHolder extends RecyclerView.ViewHolder{

        CircularImageView section_picture;
        TextView section_title;
        TextView section_text;
        RelativeLayout parentLayout;
        public ViewHolder(@NonNull View itemView) {
            super(itemView);
            section_picture = itemView.findViewById(R.id.Section_Picture);
            section_title = itemView.findViewById(R.id.title_of_section);
            section_text = itemView.findViewById(R.id.section_text);
            parentLayout = itemView.findViewById(R.id.parent_layout);
        }
    }
}
