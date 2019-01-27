#include <stdio.h>
#include <fcntl.h>
//typedef int32 (*MKDIR)(const char* name);

//typedef (* Emu_drawText)(char *str,int x,int y,int r,int g,int b,int size);

extern void emu_drawText(char *str,int x,int y,int r,int g,int b,int size);

extern void emu_drawRGB(int r,int g,int b);
extern void emu_toast(char* str);
extern int emu_createTimer(char *bstr);
extern int emu_startTimer(int id,void* data,long delay,long period);
extern void emu_refs(int x,int y,int w,int h);
extern int emu_loadImageForPak(char *bstr);
extern void emu_drawImage(int imgid,int x,int y);
extern void emu_deleteTimer(int id);
extern void emu_destroyImage(int id);
extern void emu_drawPoint(int x,int y,int r,int g,int b);
extern void emu_drawLine(int x,int y,int x2,int y2,int r,int g,int b);
extern int emu_zoomImage(int imgid,int w,int h);
extern int emu_getScrH();
extern int emu_getScrW();
extern int emu_loadImageForData(char *bstr);
extern int emu_loadImageForPath(char *bstr);


int i=1;
char *buf;
int img=10;
int img2;

int SCRW,SCRH;

int x1=1,y1=200;

void test(int data);
void test(int  data){
	
	sprintf(buf,"data:%d",img);
emu_drawRGB(200,200,200);
	
	if(i<50){
	
	
	
//sprintf(buf,"data:%d",img);
	if(i!=1)
emu_drawImage(1,x1,y1);
 emu_drawPoint(90,i,0,0,0);
 emu_drawLine(90,i,500,i*2,0,0,0);
	 emu_drawText(buf,200,i,200,50,50,32);
	
	

	 i++;
	 }else{
		// emu_deleteTimer(0);
		 
		// emu_destroyImage(0);
		 
		 i=1;}
	 
	emu_refs(0,0,720,1280);
	 
	}
int main()
{
	/*
	void *handle=dlopen("libcore.so");
	
	Emu_drawText emu_drawText=(Emu_drawText)dlsym(handle,"emu_drawText");
	*/
	buf=(char*)malloc(1024);
	printf("hello");
	

	
SCRH= emu_getScrH();
SCRW= emu_getScrW();
	
	
	
	
	
	int t=emu_createTimer("test");
	//int t2=emu_createTimer("test2");
	
//img=emu_loadImageForPak("obj/i.png");

img=emu_loadImageForPath("/storage/emulated/0/qeditor/workspace/lavatest/bin/i.png");

	img2=emu_zoomImage(0,72*2,72*2);
	
//	int tt=emu_startTimer(0,i,1000,1);
emu_drawRGB(200,200,200);

//emu_refs(0,0,720,1280);
	
	/*
	fflush(stdout);
	
     setvbuf(stdout,NULL,_IONBF,0);
     //printf("test stdout\n");
     int save_fd = dup(STDOUT_FILENO); // 保存标准输出 文件描述符 注:这里一定要用 dup 复制一个文件描述符. 不要用 = 就像是Winodws下的句柄.
     int fd = open("/sdcard/lava/log/log2.txt",(O_RDWR | O_CREAT), 0644);
     dup2(fd,STDOUT_FILENO); // 用我们新打开的文件描述符替换掉 标准输出
     printf("test file\n");
	fflush(stdout);
	*/
	return 0;
	
}



void onTouch(int action,float x,float y,int pointerIndex,int pointerCount
			,float pointersX[],float pointersY[],int pointersId[]){
				
			//	x=190;
				//(int)pointersX[pointerIndex];
			
			emu_drawRGB(200,200,0);

emu_drawImage(1,(int)pointersX[pointerIndex],(int)pointersY[pointerIndex]);

emu_refs(0,0,SCRW,SCRH);

		//	emu_toast("touch");
	
				}