package as.mke.lavrun;
import android.view.*;
import android.view.SurfaceHolder.*;
import android.content.*;

public class NativeView extends SurfaceView implements SurfaceHolder.Callback
{

	boolean isRun=false;
	public NativeView(Context c){
		super(c);
	}
	
	
	@Override
	public void surfaceCreated(SurfaceHolder p1)
	{
		// TODO: Implement this method
		
		isRun=true;
	}

	@Override
	public void surfaceChanged(SurfaceHolder p1, int p2, int p3, int p4)
	{
		// TODO: Implement this method
	}

	@Override
	public void surfaceDestroyed(SurfaceHolder p1)
	{
		isRun=false;
	}



	

}
