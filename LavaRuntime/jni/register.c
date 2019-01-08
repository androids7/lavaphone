#include <jni.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <signal.h>

#include "lava.h"


//初始化和注册部分
static char *class_path_name = "as/mke/lavrun/HelloJni";

#ifndef NELEM
#define NELEM(x) ((int)(sizeof(x) / sizeof((x)[0])))
#endif

static JNINativeMethod s_methods[] = {
	{"native_main", "(Ljava/lang/String;)V", (void*) native_main},
	{"native_result","()[B",(void*)native_result},
	/*
	{"native_createAndroid", "(Lcom/mide/Android;)V", (void*) native_createAndroid},
	{"native_exit","()V",(void*) native_exit},
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
	return result;
}


