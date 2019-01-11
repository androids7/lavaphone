package as.mke.lavrun;
import android.view.*;
import android.view.SurfaceHolder.*;
import android.content.*;
import android.graphics.*;
import java.io.*;

public class NativeView extends SurfaceView implements SurfaceHolder.Callback
{

	boolean isRun=false,back=false;
	Canvas c;
	Bitmap bp;
	
	Bitmap[] imgres;
	int bmppoint=0;
	
	
	int width,height;//屏幕分辨率
	Rect src,dst;//屏幕分辨率，屏幕缓存分辨率
	Thread td;
	SurfaceHolder holder;
	String pak=null;
	Paint bmp;
	public NativeView(Context cc,String pp){
		super(cc);
		
		holder=this.getHolder();
		holder.addCallback(this);
		setFocusable(true);
		setFocusableInTouchMode(true);
		this.pak=pp;
		init();
	}
	
	
	/*
	
	public void drawText(String str,int x,int y,int[] color,int size){
		
	}
	*/
	
	public void init(){
		
		
		setWillNotDraw(true);
		setDrawingCacheEnabled(false);
		
		bp=Bitmap.createBitmap(720,1280,Bitmap.Config.ARGB_8888);
		c=new Canvas(bp);
		height=HelloJni.height;
		width=HelloJni.width;

		src=new Rect(0,0,width,height);
		dst=new Rect(0,0,720,1280);
		
		bmp=new Paint();
		imgres=new Bitmap[255];
		
	}
	
	@Override
	public void surfaceCreated(SurfaceHolder p1)
	{
		// TODO: Implement this method
		
		isRun=true;
		/*
		td=new Thread(){
			public void run(){

				
				long t = 0 ;
				while(isRun){
					
					
				
						t = System.currentTimeMillis();
						onDraw();
						try {
							Thread.sleep(Math.max(0, 50-(System.currentTimeMillis()-t)));
						} catch (InterruptedException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
					}
					
					//if(back!=true){
					//while(!back){
					
						//}
						
						


				



			
			//}
		};
		*/
		//td.start();
		//c.drawColor(Color.WHITE);
	}

	public void onDraw(){
		
		Canvas  cc=null;
		cc=holder.lockCanvas();
					if(cc!=null){
						cc.drawBitmap(bp,dst,src,bmp);


						//if(cc!=null){
						holder.unlockCanvasAndPost(cc);
		}
	}
	
	
	
	@Override
	public void surfaceChanged(SurfaceHolder p1, int p2, int p3, int p4)
	{
		//isRun=true;
	//back=false;
	}

	@Override
	public void surfaceDestroyed(SurfaceHolder p1)
	{
		isRun=false;
		//back=true;
	}

	
	
	public InputStream readPak(String filename) throws Exception{

		return ReadFile.readFile(pak,filename);

	}
	
	
	
	public int N2J_loadImageForPak(byte[] name){
		final String path=new String(name);

		

					try
					{

						imgres[bmppoint] = BitmapFactory.decodeStream(readPak(path));

						bmppoint++;

						//nv.N2J_drawImage(bmp[bmppoint-1],50,50);

						//sho(readPak(path).available());
					}
					catch (Exception e)
					{
					
					}
					//Toast.makeText(HelloJni.this,s,0).show();


				

	
		/*

		 try
		 {
		 //
		 }
		 catch (Exception e)
		 {
		 sho(e);
		 }
		 */


		return( bmppoint-1);
		//(Object)bmp[bmppoint-1];
		//(long)(Object)bmp;
	}
	
	
	public void N2J_drawImage(int obj,int x, int y){
/*
		Rect ret=new Rect(0,0,w,h);
		RectF rf=new RectF(x,y,720,1280);
		*/
		//c.drawColor(Color.RED);
		c.drawBitmap(imgres[obj],x,y,null);
	}
	
	public void N2J_drawText(byte[] bb,int x,int y,int r,int g,int b,int size){
		int color[]=new int[3];
		color[0]=r;
		color[1]=g;
		color[2]=b;
		//c.drawColor(Color.BLUE);
		Paint p=new Paint();
		p.setColor(Color.rgb(color[0],color[1],color[2]));
		p.setTextSize(size);
		c.drawText(new String(bb),x,y,p);
	}
	public void N2J_drawRGB(int r,int g,int b){
		Paint p=new Paint();
		p.setColor(Color.rgb(r,g,b));
		c.drawRect(dst,p);
		//c.drawColor(Color.rgb(r,g,b));
	}

	public void N2J_refs(int x,int y,int w,int h){
		
		Rect rect=new Rect(x,y,w,h);
		Canvas  cc=null;
		cc=holder.lockCanvas(rect);
		if(cc!=null){
			cc.drawBitmap(bp,dst,src,bmp);


			//if(cc!=null){
			holder.unlockCanvasAndPost(cc);
		}
		
	}
}
