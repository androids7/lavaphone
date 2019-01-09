#include <jni.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <signal.h>

 #include <unistd.h>
 #include <sys/stat.h>
 #include <fcntl.h>
#include "lava.h"


//初始化和注册部分
static char *class_path_name = "as/mke/lavrun/HelloJni";

#ifndef NELEM
#define NELEM(x) ((int)(sizeof(x) / sizeof((x)[0])))
#endif

static JNINativeMethod s_methods[] = {
	{"native_main", "(Ljava/lang/String;Las/mke/lavrun/NativeView;)V", (void*) native_main},
	{"native_result","()I",(void*)native_result},
	
	{"registerTimer", "(Ljava/lang/String;J)I", (void*) registerTimer},
	
	{"runTimerMethod","(I)V",(void*)runTimerMethod},
	//{"startTimer","(I)I",(void*) },
	/*
	{"native_event","(III)V",(void*) native_event},
	{"native_init","()V",(void*) native_init},
	{"native_resume","()V",(void*) native_resume},
	{"native_pause","()V",(void*) native_pause},
	{"native_setRunC","(Ljava/lang/String;)V",(void*) native_setRunC},
    {"native_setRootDir","(Ljava/lang/String;)V",(void*) native_setRootDir},
    {"native_setScreen","(II)V",(void*) native_setScreen},
    {"native_lockBitmap","()V",(void*) native_lockBitmap},
    {"native_unLockBitmap","()V",(void*) native_unLockBitmap},
	*/
	};

static int register_methods(JNIEnv* env,char* class_name,JNINativeMethod* methods,int num_methods)
{
	jclass clazz;
	clazz = (*env)->FindClass(env, class_name);
	if (clazz == NULL) {
		return JNI_FALSE;
	}
	if ((*env)->RegisterNatives(env, clazz, methods, num_methods) < 0) {
		return JNI_FALSE;
	}
	return JNI_TRUE;
}

static int register_natives(JNIEnv *env)
{
	if(!register_methods(env, class_path_name, s_methods, NELEM(s_methods)))
		return JNI_FALSE;
		
	return JNI_TRUE;
}

//听说这是主函数？
jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved)
{
	JNIEnv* env = NULL;
	jint result = -1;
 //   mJavaVm = vm;
	if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_4) != JNI_OK) {
	   //初始化失败
	}
	
	if (register_natives(env) < 0) {
	   //注册本地方法失败
	}

	result = JNI_VERSION_1_4;
	
	
	fflush(stdout);
     setvbuf(stdout,NULL,_IONBF,0);
     //printf("test stdout\n");
     int save_fd = dup(STDOUT_FILENO); // 保存标准输出 文件描述符 注:这里一定要用 dup 复制一个文件描述符. 不要用 = 就像是Winodws下的句柄.
     int fd = open("/sdcard/lava/log/log.txt",(O_RDWR | O_CREAT), 0644);
     dup2(fd,STDOUT_FILENO); // 用我们新打开的文件描述符替换掉 标准输出
     //printf("test file\n");
	
	return result;
}


