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
	HelloJni activity;
	Paint bmp;
	
	float wh,hw;
	
	
	public NativeView(Context cc,String pp,HelloJni activity){
		super(cc);
		
		holder=this.getHolder();
		holder.addCallback(this);
		this.activity=activity;
		
	
		
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
		wh=720/width;
		hw=1280/height;
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

	
	
	private static final int MAX_POINTER_NUMBER=10;
	private float pointersX[]=new float[MAX_POINTER_NUMBER];
	private float pointersY[]=new float[MAX_POINTER_NUMBER];
	private int   pointersId[]=new int[MAX_POINTER_NUMBER];

	
	@Override
	public boolean onTouchEvent(MotionEvent event) {
		//MotionEvent.ACTION_DOWN 
		/*
		Paint nn=new Paint();
		nn.setColor(Color.YELLOW);
		nn.setTextSize(80);
		c.drawText("touch acreen",200,200,nn);
		*/
		int count=event.getPointerCount();
		if(count>MAX_POINTER_NUMBER)
			count=MAX_POINTER_NUMBER;
		for(int i=0;i<count;i++)
		{
			pointersX[i]=event.getX(i)*720/width;
			pointersY[i]=event.getY(i)*1280/height;
			pointersId[i]=event.getPointerId(i);
		}

		return activity.touchEvent(event.getAction(),event.getX(),event.getY(),event.getActionIndex(),count
										  ,pointersX,pointersY,pointersId);
	}
	
	
	
	
	
	public InputStream readPak(String filename) throws Exception{

		return ReadFile.readFile(pak,filename);

	}
	
	
	public void N2J_destroyImage(int id){
		imgres[id].recycle();
	}
	
	
	public int N2J_loadImageForExt(byte[] name){
		
		imgres[bmppoint]=BitmapFactory.decodeFile(new String(name));
		
		
		bmppoint++;
		
		return (bmppoint-1);
	}
	
	public int N2J_loadImageForByte(byte[] data){
		
		imgres[bmppoint]=BitmapFactory.decodeByteArray(data,0,data.length);
		bmppoint++;
		
		return (bmppoint-1);
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
	
	public void N2J_drawPoint(int x,int y,int r,int g,int b){
		Paint pp=new Paint();
		pp.setColor(Color.rgb(r,g,b));
		c.drawPoint(x,y,pp);
	}
	
	public void N2J_drawLine(int x1,int y1,int x2,int y2,int r,int g,int b){
		
		Paint pp=new Paint();
		pp.setColor(Color.rgb(r,g,b));
		c.drawLine(x1,y1,x2,y2,pp);
	}
	
	public int N2J_zoomImage(int bmpid,int width,int height){
	  imgres[bmppoint]=zoomImg(imgres[bmpid],width,height);
	  bmppoint++;
	  return (bmppoint-1);
	}
	
	public  Bitmap zoomImg(Bitmap bm, int newWidth ,int newHeight){
		// 获得图片的宽高
		int width = bm.getWidth();
		int height = bm.getHeight();
		// 计算缩放比例
		float scaleWidth = ((float) newWidth) / width;
		float scaleHeight = ((float) newHeight) / height;
		// 取得想要缩放的matrix参数
		Matrix matrix = new Matrix();
		matrix.postScale(scaleWidth, scaleHeight);
		// 得到新的图片
		Bitmap newbm = Bitmap.createBitmap(bm, 0, 0, width, height, matrix, true);
		return newbm;
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
	
	
	public int N2J_getScrW(){
		return width;
	}
	
	public int N2J_getScrH(){
		return height;
	}
}
