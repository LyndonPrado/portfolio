package com.example.lyndon.portfolio_app_java;

import android.app.Activity;
import android.content.Context;
import android.graphics.Color;
import android.support.annotation.NonNull;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;
import com.bumptech.glide.Glide;
import com.mikhaellopez.circularimageview.CircularImageView;

import java.util.ArrayList;

public class RecylerViewAdapter extends RecyclerView.Adapter<RecylerViewAdapter.ViewHolder> {
    private static final String TAG = "RecylerViewAdapter";

    private ArrayList<String> mImageNames = new ArrayList<>();
    private ArrayList<String> mImages = new ArrayList<>();
    private Context mContext;

    public RecylerViewAdapter(Context mContext, ArrayList<String> mImageNames, ArrayList<String> mImages) {
        this.mImageNames = mImageNames;
        this.mImages = mImages;
        this.mContext = mContext;
    }

    @NonNull
    @Override
    public ViewHolder onCreateViewHolder(@NonNull ViewGroup viewGroup, int i) {
        View view = LayoutInflater.from(viewGroup.getContext()).inflate(R.layout.layout_listitem,viewGroup,false);
        ViewHolder holder = new ViewHolder(view);
        return holder;
    }

    @Override
    public void onBindViewHolder(@NonNull ViewHolder viewHolder, final int i) {
        Log.d(TAG,"onBindViewHolder: called.");
//        Glide.with(mContext)
//                .asBitmap()
//                .load(mImages.get(i))
//                .into(viewHolder.image);
        CircularImageView view = (CircularImageView)((Activity)this.mContext).findViewById(R.id.profile_picture);
        viewHolder.image = view;
        viewHolder.imageName.setText(mImageNames.get(i));
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

        CircularImageView image;
        TextView imageName;
        RelativeLayout parentLayout;
        public ViewHolder(@NonNull View itemView) {
            super(itemView);
            image = itemView.findViewById(R.id.profile_picture);
            imageName = itemView.findViewById(R.id.about_me_title);
            parentLayout = itemView.findViewById(R.id.parent_layout);

        }
    }
}
