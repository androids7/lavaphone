
package as.mke.lavrun;

import android.app.Activity;
import android.widget.TextView;
import android.os.Bundle;
import android.support.v4.app.ActivityCompat;
import android.content.pm.*;
import java.io.*;
import android.view.*;

public class HelloJni extends Activity
{
    /** Called when the activity is first created. */
	
	static int width,height;
	static String fpath="/data/data/as.mke.lavrun/files";
	
	NativeView nv;
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

		requestWindowFeature(1);
		Display mDisplay = getWindowManager().getDefaultDisplay();
		width = mDisplay.getWidth();
		height = mDisplay.getHeight();
		
		
      verifyStoragePermissions(this);
		native_main("/sdcard/0/lavatest.so");
        //TextView tv=new TextView(this);
		System.load("/data/data/as.mke.lavrun/files/librun.so");
		//tv.setText(new String(native_result()));
		nv=new NativeView(this);
        setContentView(nv);
		//R.layout.main);
    }

	public void N2J_drawText(String s,int x,int y,int r,int g,int b,int size){
		int bn[]=new int[3];
		bn[0]=r;
		bn[1]=g;
		bn[2]=b;
		nv.drawText(s,x,y,bn,size);
	}
	
	
	
	
	
	private static final int REQUEST_EXTERNAL_STORAGE = 1;
    private static String[] PERMISSIONS_STORAGE = {
		"android.permission.READ_EXTERNAL_STORAGE",
		"android.permission.WRITE_EXTERNAL_STORAGE" };


    public static void verifyStoragePermissions(Activity activity) {

		
		File file=new File(fpath);
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
	
	
    
    public native void  native_main(String path);

  
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
