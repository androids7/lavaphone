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


int i=1;
char *buf;
int img=10;



void test(int data);
void test(int  data){
	
	sprintf(buf,"data:%d",img);
emu_drawRGB(200,200,200);
	emu_toast(buf);
	
	if(i<400){
	
	
	
//sprintf(buf,"data:%d",img);
	
 emu_drawImage(0,100,i);
	 emu_drawText(buf,200,i,200,50,50,32);
	
	

	 i++;
	 }else{
		 
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
	

	

	
	
	
	int t=emu_createTimer("test");
	//int t2=emu_createTimer("test2");
	int tt=emu_startTimer(0,i,100,1);
emu_drawRGB(200,200,200);
img=emu_loadImageForPak("i.png");
	
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
