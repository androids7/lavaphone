package as.mke.lavrun;
import android.view.*;
import android.view.SurfaceHolder.*;
import android.content.*;
import android.graphics.*;

public class NativeView extends SurfaceView implements SurfaceHolder.Callback
{

	boolean isRun=false,back=false;
	Canvas c;
	Bitmap bp;
	
	
	int width,height;//屏幕分辨率
	Rect src,dst;//屏幕分辨率，屏幕缓存分辨率
	Thread td;
	SurfaceHolder holder;
	
	
	public NativeView(Context cc){
		super(cc);
		
		holder=this.getHolder();
		holder.addCallback(this);
		setFocusable(true);
		setFocusableInTouchMode(true);
		init();
	}
	
	
	
	
	public void drawText(String str,int x,int y,int[] color,int size){
		c.drawColor(Color.BLUE);
		Paint p=new Paint();
		p.setColor(Color.rgb(color[0],color[1],color[2]));
		p.setTextSize(size);
		c.drawText(str,x,y,p);
	}
	
	
	public void init(){
		
		bp=Bitmap.createBitmap(720,1280,Bitmap.Config.ARGB_8888);
		c=new Canvas(bp);
		height=HelloJni.height;
		width=HelloJni.width;

		src=new Rect(0,0,width,height);
		dst=new Rect(0,0,720,1280);
		
		
		
		td=new Thread(){
			public void run(){
				while(isRun){
					//if(back!=true){
				Canvas cc=holder.lockCanvas();
				cc.drawBitmap(bp,dst,src,null);
				if(cc!=null){
					holder.unlockCanvasAndPost(cc);
				}
				
				}
				
				
				
				}
			//}
		};
	}
	
	@Override
	public void surfaceCreated(SurfaceHolder p1)
	{
		// TODO: Implement this method
		
		isRun=true;
		td.start();
	}

	@Override
	public void surfaceChanged(SurfaceHolder p1, int p2, int p3, int p4)
	{
		
	}

	@Override
	public void surfaceDestroyed(SurfaceHolder p1)
	{
		isRun=false;
	}



	

}
