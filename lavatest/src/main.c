#include <stdio.h>
#include <fcntl.h>
//typedef int32 (*MKDIR)(const char* name);

//typedef (* Emu_drawText)(char *str,int x,int y,int r,int g,int b,int size);

extern void emu_drawText(char *str,int x,int y,int r,int g,int b,int size);


char *out()
{
	/*
	void *handle=dlopen("libcore.so");
	
	Emu_drawText emu_drawText=(Emu_drawText)dlsym(handle,"emu_drawText");
	*/
	 emu_drawText("hello",200,120,200,50,50,32);
	printf("hello");
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
	return "hello world!";
	
}