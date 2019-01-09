#include"lava.h"
#include "lavadev.h"
#include <dlfcn.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define  BUFFSIZE  1024     // 缓冲区大小

 char *sofile="/data/data/as.mke.lavrun/files/librun.so";
 
 jstring stoJstring(JNIEnv* env, const char* pat);
 
 char* jstringTostring(JNIEnv* env, jstring jstr) ;
 
 void* handle=NULL;
 
 JNIEnv *mVmJniEnv;
 
 static jobject obj_emulator;
 static jobject obj_emuScreen;
 
 static jmethodID id_drawText; //发送短信
static jmethodID id_drawRGB; //刷新画布
static jmethodID id_createTimer; //结束Activity 
static jmethodID id_startTimer; //Toast显示
 
 
 
 
 
 
 
void file_copy(char *srcFile,char *desFile);


void initJniId(JNIEnv * env, jobject obj);



typedef int(*main_t)();
typedef void(*timers_t)();

timers_t timer[255];
int timerpoint=0;
inline getJniEnv()
{
   return mVmJniEnv;
}




void native_main(JNIEnv *env, jobject obj,jstring path,jobject emuScreen){
	
	char *sopath=(char*)malloc(1024);
	sopath=jstringTostring(env,path);
	
	file_copy(sopath,sofile);
	    obj_emulator = (*env)->NewGlobalRef(env, obj);
		obj_emuScreen = (*env)->NewGlobalRef(env, emuScreen);
	
		mVmJniEnv = env;
	initJniId(env, obj);
	
	
}




void runTimerMethod(JNIEnv *env, jobject obj,jint point){
	
	timer[point]();
	
}
//返回函数指针
int registerTimer(JNIEnv *env, jobject obj,jstring str)
{
	//JNIEnv *env=getJniEnv();
	char *bstr=jstringTostring(env,str);
	timer[timerpoint]= (timers_t) dlsym(handle,bstr);
	timerpoint++;
	/*
	
	jbyteArray data = (*env)->NewByteArray(env, strlen(bstr));
(*env)->SetByteArrayRegion(env, data, 0, strlen(bstr), bstr);
   
	  (*env)->CallVoidMethod(env,obj_emulator,id_createTimer,data,(jlong)time);
*/
	return (timerpoint-1);
}



//……………………实现库函数……………………………

//创建定时器
int emu_createTimer(char *bstr){
	
	
	JNIEnv *env=getJniEnv();
	jbyteArray data = (*env)->NewByteArray(env, strlen(bstr));
(*env)->SetByteArrayRegion(env, data, 0, strlen(bstr), bstr);
   
	return  (*env)->CallIntMethod(env,obj_emulator,id_createTimer,data);

}

int emu_startTimer(int id,long delay){
	
	
	JNIEnv *env=getJniEnv();
	
	
	return  (*env)->CallIntMethod(env,obj_emulator,id_startTimer,id,(jlong)delay);

	
}


jbyteArray geterror(JNIEnv * env, jobject obj){
	char *res=(char*)malloc(4096);
	res=dlerror();
	jbyteArray data = (*env)->NewByteArray(env, strlen(res));
(*env)->SetByteArrayRegion(env, data, 0, strlen(res), res);
   
	
	return data;
	
}
// 绘制颜色清屏
void emu_drawText(char *res,int x,int y,int r,int g,int b,int size)
{
	
   JNIEnv *env=getJniEnv();
  
   //char *res=(char*)malloc(1024);

//dlclose(handle);
//jsize length=(jsize)sizeof(res);
jbyteArray data = (*env)->NewByteArray(env, strlen(res));
(*env)->SetByteArrayRegion(env, data, 0, strlen(res), res);
   
   (*env)->CallVoidMethod(env,obj_emuScreen,id_drawText,data,(jint)x,(jint)y,(jint)r,(jint)g,(jint)b,(jint)size);
}

void emu_drawRGB(int r,int g,int b){
	JNIEnv *env=getJniEnv();
   (*env)->CallVoidMethod(env,obj_emuScreen,id_drawRGB,(jint)r,(jint)g,(jint)b);

}

//注册java方法
void initJniId(JNIEnv * env, jobject obj)
{
    //Emulator
    jclass cls = (*env)->GetObjectClass(env, obj_emulator);
	id_createTimer = (*env)->GetMethodID(env, cls, "N2J_createTimer", "([B)I");
	
	id_startTimer = (*env)->GetMethodID(env, cls, "N2J_startTimer", "(IJ)I");
	/*
    id_web = (*env)->GetMethodID(env, cls, "N2J_web", "(Ljava/lang/String;)V");
    id_lcd = (*env)->GetMethodID(env, cls, "N2J_lcdLong", "(I)V");
    id_getuptime = (*env)->GetMethodID(env, cls, "N2J_getUptime", "()J");
    id_spcreate = (*env)->GetMethodID(env, cls, "N2J_spCreate", "(Ljava/lang/String;)V");
    id_spputint = (*env)->GetMethodID(env, cls, "N2J_putInt", "(Ljava/lang/String;I)V");
    id_spputstr = (*env)->GetMethodID(env, cls, "N2J_putString", "(Ljava/lang/String;Ljava/lang/String;)V");
    id_spgetint = (*env)->GetMethodID(env, cls, "N2J_getInt", "(Ljava/lang/String;)I");
    id_spgetstr = (*env)->GetMethodID(env, cls, "N2J_getString", "(Ljava/lang/String;)Ljava/lang/String;");
    id_videoPlayer = (*env)->GetMethodID(env, cls, "N2J_videoPlayer", "(Ljava/lang/String;)V");
    id_musicPlayer = (*env)->GetMethodID(env, cls, "N2J_musicPlayer", "(Ljava/lang/String;I)V");
    id_sendSms = (*env)->GetMethodID(env,cls,"N2J_sendSms","(Ljava/lang/String;Ljava/lang/String;I)I");
    id_webBrowser = (*env)->GetMethodID(env,cls,"N2J_webBrowser","(Ljava/lang/String;)V");
	*/
	(*env)->DeleteLocalRef(env, cls);
    
    //EmuView
    cls = (*env)->GetObjectClass(env, obj_emuScreen);
  //  id_textWH = (*env)->GetMethodID(env, cls, "N2J_textWH", "(Ljava/lang/String;III)V");
	id_drawText = (*env)->GetMethodID(env, cls, "N2J_drawText", "([BIIIIII)V");
	
    id_drawRGB = (*env)->GetMethodID(env, cls, "N2J_drawRGB", "(III)V");
	/*
    id_drawRect = (*env)->GetMethodID(env, cls, "N2J_drawRect", "(IIIIIII)V");
    id_drawPoint = (*env)->GetMethodID(env, cls, "N2J_drawPoint", "(IIIII)V");
    id_drawLine = (*env)->GetMethodID(env, cls, "N2J_drawLine", "(IIIIIII)V");
    id_drawCircle = (*env)->GetMethodID(env, cls, "N2J_drawCircle", "(IIIIII)V");
    id_drawEffsetion = (*env)->GetMethodID(env, cls, "N2J_drawEffsetion", "(IIIIIII)V");
	id_refresh = (*env)->GetMethodID(env, cls, "N2J_refresh", "(IIII)V");
	*/
    (*env)->DeleteLocalRef(env, cls);
  /*
    //Audio
    cls = (*env)->GetObjectClass(env, obj_emuAudio);
	id_startshake = (*env)->GetMethodID(env, cls, "N2J_startShake", "(I)V");
	id_stopshake = (*env)->GetMethodID(env, cls, "N2J_stopShake", "()V");
    id_soundinit = (*env)->GetMethodID(env, cls, "N2J_playSoundExInit", "(I)I");
	id_soundloadfile = (*env)->GetMethodID(env, cls, "N2J_playSoundExLoadFile", "(ILjava/lang/String;)I");
	id_soundplay = (*env)->GetMethodID(env, cls, "N2J_playSoundEx", "(III)I");
	id_soundpause = (*env)->GetMethodID(env, cls, "N2J_pauseSoundEx", "(I)I");
	id_soundstop = (*env)->GetMethodID(env, cls, "N2J_stopSoundEx", "(I)I");
	id_soundresume = (*env)->GetMethodID(env, cls, "N2J_resumeSoundEx", "(I)I");
	id_soundclose = (*env)->GetMethodID(env, cls, "N2J_closeSoundEx", "(I)I");
	id_setvolume = (*env)->GetMethodID(env, cls, "N2J_setVolume", "(I)I");
	id_getSoundAllTime = (*env)->GetMethodID(env, cls, "N2J_getSoundTotalTime", "(I)I");
	id_getSoundNowTime = (*env)->GetMethodID(env, cls, "N2J_getSoundCurTime", "(I)I");
	id_getSoundNowTimes = (*env)->GetMethodID(env, cls, "N2J_getSoundCurTimeMs", "(I)I");
	id_setplaypos = (*env)->GetMethodID(env, cls, "N2J_setPlayPos", "(II)I");
	id_setplaytime = (*env)->GetMethodID(env, cls, "N2J_setPlayTime", "(II)I");
	id_getdevicestate = (*env)->GetMethodID(env, cls, "N2J_getDeviceState", "(I)I");
    (*env)->DeleteLocalRef(env, cls);
	*/
	
}



jbyteArray native_result(JNIEnv *env,jobject obj){
	
	
	handle=dlopen("librun.so",RTLD_LAZY);
	
	main_t maim = (main_t) dlsym(handle,"main");

char *res=(char*)malloc(1024);
	
res="oooo";

//res=dlerror();

maim();
//int res=maim();

//dlclose(handle);
//jsize length=(jsize)sizeof(res);

jbyteArray data = (*env)->NewByteArray(env, strlen(res));
(*env)->SetByteArrayRegion(env, data, 0, strlen(res), res);
//使用数据
//(*env)->DeleteLocalRef(env, data);
return data;

//return res;
	//return stoJstring(env,res);
}


char* jbytearrayToChars(JNIEnv *env, jbyteArray bytearray)
{
	//char *chars = NULL;
jbyte *bytes;
bytes = (*env)->GetByteArrayElements(env,bytearray, 0);
int chars_len = (*env)->GetArrayLength(env,bytearray);
char * chars [chars_len + 1];
memset(chars,0,chars_len + 1);
memcpy(chars, bytes, chars_len);
chars[chars_len] = 0;
(*env)->ReleaseByteArrayElements(env,bytearray, bytes, 0);
return chars;
}


//jstring to char* 
char* jstringTostring(JNIEnv* env, jstring jstr) 
{ 
       char* rtn = NULL; 
       jclass clsstring = (*env)->FindClass(env,"java/lang/String"); 
       jstring strencode = (*env)->NewStringUTF(env,"utf-8"); 
       jmethodID mid = (*env)->GetMethodID(env,clsstring, "getBytes", "(Ljava/lang/String;)[B"); 
       jbyteArray barr= (jbyteArray)(*env)->CallObjectMethod(env,jstr, mid, strencode); 
       jsize alen = (*env)->GetArrayLength(env,barr); 
       jbyte* ba = (*env)->GetByteArrayElements(env,barr, JNI_FALSE); 
       if (alen > 0) 
       { 
                 rtn = (char*)malloc(alen + 1); 
                 memcpy(rtn, ba, alen); 
                 rtn[alen] = 0; 
       } 
     (*  env)->ReleaseByteArrayElements(env,barr, ba, 0); 
       return rtn; 
}

//char* to jstring 
jstring stoJstring(JNIEnv* env, const char* pat) 
{ 
       jclass strClass =(* env)->FindClass(env,"Ljava/lang/String;"); 
       jmethodID ctorID = (*env)->GetMethodID(env,strClass, "<init>", "([BLjava/lang/String;)V"); 
       jbyteArray bytes = (*env)->NewByteArray(env,strlen(pat)); 
     (*  env)->SetByteArrayRegion(env,bytes, 0, strlen(pat), (jbyte*)pat); 
       jstring encoding = (*env)->NewStringUTF(env,"utf-8"); 
       return (jstring)(*env)->NewObject(env,strClass, ctorID, bytes, encoding); 
}

//可以复制任意大小的文件 
void file_copy(char *srcFile,char *desFile){
	
	FILE *fin;  // 源文件
    FILE *fout; // 目标文件
    char *buff; // 缓冲区指针
	int ret;
	
	/* 以读的方式打开源文件 */
    fin = fopen(srcFile, "r");
    if (NULL == fin)    // 检查打开情况
    {
        perror(srcFile);
       return -2;
    }

    /* 以写的方式打开目标文件 */
    fout = fopen(desFile,"w");
    if (NULL == fout)   // 检查打开情况
    {
        perror(desFile);
        goto err0;
    }

    /* 分配缓冲区内存空间 */
    buff = malloc(BUFFSIZE);
    if (NULL == buff)   // 检查分配空间是否成功
    {
        fprintf(stderr, "molloc failed\n");
        goto err1;
    }

    /* 循环读写文件 */
    while (1)
    {
        /* 从源文件中读取内容 */
       ret= fread(buff, 1, BUFFSIZE, fin);

        /* 把从源文件读取到的容写入到目标文件中 */
        if (ret != BUFFSIZE)
        {
            fwrite(buff, ret, 1, fout);
        }
        else
        {
            fwrite(buff, BUFFSIZE, 1, fout);
        }

        if (feof(fin))
            break;
    }

    /* 关闭打开的文件 */
	/*
    fclose(fin);
    fclose(fout);

    // 释放动态分配的内存空间 
    free(buff);
	
	"/
	/* 出错时的层次退出 */
err2:
    free(buff);
err1:
    fclose(fout);
err0:
    fclose(fin);
	
}




