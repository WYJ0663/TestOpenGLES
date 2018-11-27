package com.example.testopengles;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;
import android.os.Handler;
import android.os.HandlerThread;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private Handler mHandler;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private SurfaceView mSurfaceView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

        HandlerThread handlerThread = new HandlerThread("draw");
        handlerThread.start();
        mHandler = new Handler();

        mSurfaceView = findViewById(R.id.surface);
        mSurfaceView.getHolder().addCallback(new SurfaceHolder.Callback() {
            @Override
            public void surfaceCreated(SurfaceHolder holder) {
                display(holder.getSurface());
            }

            @Override
            public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

            }

            @Override
            public void surfaceDestroyed(SurfaceHolder holder) {

            }
        });

    }

    public void onDraw(View view) {
//         draw2(view);
        draw3(view);
    }

    private void draw4(View view) {
        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inPreferredConfig = Bitmap.Config.ARGB_8888;
        Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.mipmap.wall, options);
        int w = bitmap.getWidth(), h = bitmap.getHeight();
        Log.e("yijun", "wh=" + w + "-" + h);
        byte[] pixB = new byte[w * h * 4];

        for (int i = 0; i < w; i++) {
            for (int j = 0; j < w; j++) {
                int c = bitmap.getPixel(i,j);
                int R = (c >> 16) & 0xff;
                int G = (c >> 8) & 0xff;
                int B = c & 0xff;

                pixB[i * 3 + 0] = (byte) R;
                pixB[i * 3 + 1] = (byte) G;
                pixB[i * 3 + 2] = (byte) B;
                pixB[i * 3 + 3] = (byte) 0xFF;
            }
        }
        view.setBackgroundDrawable(new BitmapDrawable(bitmap));
        draw(pixB,w,h);
    }

    private void draw3(View view) {
        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inPreferredConfig = Bitmap.Config.ARGB_4444;
        Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.mipmap.wall, options);
        view.setBackgroundDrawable(new BitmapDrawable(bitmap));
        drawBitmap(bitmap);
    }

    private void draw2(View view) {
        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inPreferredConfig = Bitmap.Config.ARGB_8888;
        Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.mipmap.saber, options);
        int w = bitmap.getWidth(), h = bitmap.getHeight();
        int[] pix = new int[w * h];
        bitmap.getPixels(pix, 0, w, 0, 0, w, h);
        Log.e("yijun", "wh=" + w + "-" + h);
        byte[] pixB = new byte[pix.length * 3];

        for (int i = 0; i < pix.length; i++) {
            int c = pix[i];
            int A = (c >> 24) & 0xff;
            int R = (c >> 16) & 0xff;
            int G = (c >> 8) & 0xff;
            int B = c & 0xff;

//            pixB[i * 3 + 0] = (byte) A;
            pixB[i * 3 + 0] = (byte) R;
            pixB[i * 3 + 1] = (byte) G;
            pixB[i * 3 + 2] = (byte) B;
        }
        Bitmap bitmap2 = Bitmap.createBitmap(pix, w, h, Bitmap.Config.ARGB_4444);
        view.setBackgroundDrawable(new BitmapDrawable(bitmap2));
        draw(pixB,w,h);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native void display(Surface surface);

    public native void draw(byte[] pix, int w, int h);

    public native void drawBitmap(Bitmap bitmap);
}
