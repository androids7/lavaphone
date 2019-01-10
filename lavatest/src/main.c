#include <stdio.h>
#include <fcntl.h>
//typedef int32 (*MKDIR)(const char* name);

//typedef (* Emu_drawText)(char *str,int x,int y,int r,int g,int b,int size);

extern void emu_drawText(char *str,int x,int y,int r,int g,int b,int size);

extern void emu_drawRGB(int r,int g,int b);
extern void emu_toast(char* str);
extern int emu_createTimer(char *bstr);
extern int emu_startTimer(int id,void* data,long delay,long period);
int i=1;
char *buf;


void test(int data);
void test(int  data){
	
	sprintf(buf,"data:%d",data);
//emu_drawRGB(200,(int)data,200);
	emu_toast(buf);
	 emu_drawText(buf,200,120*i,200,50,50,32);
i++;
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
	int tt=emu_startTimer(0,i,(long)1000,3);
emu_drawRGB(0,200,200);
	
	
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
