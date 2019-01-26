
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
import android.graphics.*;

public class HelloJni extends Activity
{
    /** Called when the activity is first created. */
	
	static int width,height;
	static String fpath="/data/data/as.mke.lavrun/files";
	
	NativeView nv;

	Timer[] time=null;
	BackTask[] task=null;
	
	
	//Bitmap[] bmp;
	
	
	int timepoint=0;
	
	//HashMap<Integer,Timer> timemap;
	Handler hd;
	String pak="/sdcard/qeditor/workspace/lavatest/bin/lavatest.zip";
	TextView tv;
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

		requestWindowFeature(1);
		Display mDisplay = getWindowManager().getDefaultDisplay();
		width = mDisplay.getWidth();
		height = mDisplay.getHeight();
		
		
      verifyStoragePermissions(this);
	  
		//setContentView(R.layout.main);
	  
	  
	  
		//nv=(NativeView)findViewById(R.id.mainNativeView1);
		nv=new NativeView(this,pak);
		nv.setZOrderOnTop(true);
		setContentView(nv);
		init();
		
		       tv=new TextView(this);
		unpakso();
		native_main(pak,nv);
		
		
		
		System.load("/data/data/as.mke.lavrun/files/librun.so");
		tv.setText("result:"+new String(native_result()));
		
		
        /*
		LinearLayout l=(LinearLayout)findViewById(R.id.mainLinearLayout1);
		
		l.addView(tv);
		*/
		//l.addView(nv);
		
		//nv.drawText("ooooo",100,200,new int[]{200,0,0},100);
		//R.layout.main);
    }

	
	public void unpakso(){
		
		File file=new File("sdcard/lava/tmp");
		file.mkdir();
		
		try
		{
			InputStream in=ReadFile.readFile(pak,"lavatest.so");
			ByteArrayOutputStream bao=new ByteArrayOutputStream();
			
			int temp=0;
			byte b[]=new byte[1024];
			
			while((temp=in.read(b))!=-1){
				bao.write(b,0,temp);
			}
			
			bao.close();
			file=new File("sdcard/lava/tmp/libgo.so");
			
			FileOutputStream ou=new FileOutputStream(file);
			
			ou.write(bao.toByteArray());
			
			ou.close();
			
			
			
			
			
		}
		catch (Exception e)
		{}
	}
	
	public void N2J_deleteTimer(int id){
		time[id].cancel();
		task[id].cancel();
		time[id]=null;
		
		task[id]=null;
	}
	
	
	
	public int N2J_createTimer( byte[] methodname){
		
		/*
		TimerTask task=new TimerTask(){
			public void run(){
				
				runTimerMethod(new String(methodname));
			}
		};*/
		timepoint++;
	//sho(new String(methodname));
	/*
	new Thread(){
		public void run(){
			
			Message msg=new Message();
			msg.obj=new String(geterror());
		hd.sendMessage(msg);
		
		
		}
		}.start();
		*/
		return registerTimer(new String(methodname));
		}
	
		public int N2J_startTimer(int id,long datas,long delay,long period){
			try{
				//time[timepoint]=new Timer();
			//	Timer t=new Timer();
				//sho("timepoint:"+(timepoint-1)+"id:"+id);
				time[timepoint-1].purge();
			
			//	task[timepoint]=new BackTask();
				task[timepoint-1].methodid=id;
				task[timepoint-1].data=datas;
			time[timepoint-1].schedule(task[timepoint-1],delay,period);
			/*
			new TimerTask(){
				@Override
				public void run(){

						
					}
				},delay);
				*/
			//t.schedule(tt,delay);
			//timemap.put(timepoint,t);
			
				}catch(Exception e){
					sho(e+" "+timepoint);
				}
				
			
				
			return timepoint;
				
		}
		public void destroyTimer(int id){
			time[id].cancel();
		}
		
		
	public void init(){
		
		

		 time=new Timer[255];
		 task=new BackTask[255];
		// bmp=new Bitmap[255];
		// timemap=new HashMap<Integer,Timer>();
	
		 for(int i=0;i<255;i++){
			 time[i]=new Timer();
			 task[i]=new BackTask();
			 
		 }
		 
		 
		hd=new Handler(){
			
			public void handleMessage(Message msg){
				super.handleMessage(msg);
				
				switch(msg.what){
					case 0x111:
						sho(msg.obj.toString());
						//("call handle");
						//tv.setText(new String(geterror()));
						
						/*
						List<Object> li=(List)msg.obj;
						nv.drawText(li.get(0).toString(),(int)li.get(1),(int)li.get(2),(int[])li.get(3),(int)li.get(4));
						sho("draw");
						*/
					break;
					
					case 0x112:
						List<Object> li=(ArrayList<Object>)msg.obj;
						int methodid=li.get(0);
						long data=li.get(1);
						runTimerMethod(methodid,data);
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
		
		
		
	
    public  void verifyStoragePermissions(Activity activity) {

		
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
	
	
	
	
	
	
	
	public void N2J_Toast(byte[] str){
		
		
		final Message msg=new Message();
		msg.what=0x111;
		msg.obj=new String(str);
		
		runOnUiThread(new Runnable(){

				public void run(){

     hd.sendMessage(msg);
					//Toast.makeText(HelloJni.this,s,0).show();


				}

			});
		
	}
	
	
    
    public native void  native_main(String path,NativeView nv);

	
  
	public native int registerTimer(String methodname);
	
	public native void runTimerMethod(int id,long data);
	public  native byte[] native_result();
    public native byte[] geterror();
    static {
        System.loadLibrary("core");
    }

	@Override
	protected void onPause()
{
 // TODO: Implement this method
 
super.onPause();
//nv.back=true;
}

@Override
protected void onResume()
{
	// TODO: Implement this method
	super.onResume();
	//nv.back=false;
}
	
	
	class BackTask extends TimerTask
	{

		int methodid=0;
		long data=0;
		@Override
		public void run()
		{
			Message msg=new Message();
			List<Object> li=new ArrayList<Object>();
			li.add(methodid);
			li.add(data);
			msg.obj=li;
			msg.what=0x112;
			hd.sendMessage(msg);
			
			/*
			runOnUiThread(new Runnable(){
				
				public void run(){
				
			
		//	hd.sendEmptyMessage(0x111);
			
			
			}
			
			});*/
		}

		
	}
}
