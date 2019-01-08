
package as.mke.lavrun;

import android.app.Activity;
import android.widget.TextView;
import android.os.Bundle;
import android.support.v4.app.ActivityCompat;
import android.content.pm.*;
import java.io.*;
import android.view.*;
import android.os.*;
import java.util.*;
import android.widget.*;

public class HelloJni extends Activity
{
    /** Called when the activity is first created. */
	
	static int width,height;
	static String fpath="/data/data/as.mke.lavrun/files";
	
	NativeView nv;
	
	Handler hd;
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

		requestWindowFeature(1);
		Display mDisplay = getWindowManager().getDefaultDisplay();
		width = mDisplay.getWidth();
		height = mDisplay.getHeight();
		
		
      verifyStoragePermissions(this);
		nv=new NativeView(this);
	  
		native_main("/sdcard/0/lavatest.so",nv);
        TextView tv=new TextView(this);
		System.load("/data/data/as.mke.lavrun/files/librun.so");
		tv.setText(new String(native_result()));
		
        setContentView(R.layout.main);
		LinearLayout l=(LinearLayout)findViewById(R.id.mainLinearLayout1);
		
		l.addView(tv);
		l.addView(nv);
		init();
		//nv.drawText("ooooo",100,200,new int[]{200,0,0},100);
		//R.layout.main);
    }

	
	
	
	public void init(){
		hd=new Handler(){
			
			public void handleMessage(Message msg){
				super.handleMessage(msg);
				
				switch(msg.what){
					case 0x111:
						/*
						List<Object> li=(List)msg.obj;
						nv.drawText(li.get(0).toString(),(int)li.get(1),(int)li.get(2),(int[])li.get(3),(int)li.get(4));
						sho("draw");
						*/
					break;
				}
			}
		};
	}
	
	
	private static final int REQUEST_EXTERNAL_STORAGE = 1;
    private static String[] PERMISSIONS_STORAGE = {
		"android.permission.READ_EXTERNAL_STORAGE",
		"android.permission.WRITE_EXTERNAL_STORAGE" };


		
		public void sho(Object o){
			Toast.makeText(this,o.toString(),0).show();
		}
    public static void verifyStoragePermissions(Activity activity) {

		
		File file=new File(fpath);
		if(!file.exists()){
			file.mkdir();
		}
		
		file=new File("sdcard/lava");
		if(!file.exists()){
			file.mkdir();
		}
		
		file=new File("sdcard/lava/log");
		if(!file.exists()){
			file.mkdir();
		}
		
		
        try {
			//检测是否有写的权限
            int permission = ActivityCompat.checkSelfPermission(activity,
																"android.permission.WRITE_EXTERNAL_STORAGE");
            if (permission != PackageManager.PERMISSION_GRANTED) {
				// 没有写的权限，去申请写的权限，会弹出对话框
                ActivityCompat.requestPermissions(activity, PERMISSIONS_STORAGE,REQUEST_EXTERNAL_STORAGE);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
	
	
    
    public native void  native_main(String path,NativeView nv);

  
	public  native byte[] native_result();
    
    static {
        System.loadLibrary("core");
    }

	@Override
	protected void onPause()
{
 // TODO: Implement this method
 
super.onPause();
nv.back=true;
}

@Override
protected void onResume()
{
	// TODO: Implement this method
	super.onResume();
	nv.back=false;
}
	
	
	
}
