#include"lava.h"
#include "lavadev.h"
#include <dlfcn.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <zlib.h>

#include <android/bitmap.h>

#define  BUFFSIZE  1024     // 缓冲区大小

 char *sofile="/data/data/as.mke.lavrun/files/librun.so";
 char *tfile="/sdcard/lava/tmp/";
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
 
static jmethodID id_deleteTimer;


 static jmethodID id_toast;
 
 static jmethodID id_refs;
 
 static jmethodID id_loadimageforpak;
 
 static jmethodID id_drawImage;
 
 
 static jmethodID id_loadimageforpath;
 static jmethodID id_loadimageforbyte;
 static jmethodID id_loadimageforext;
 
 static jmethodID id_destroyImage;
 
 static jmethodID id_drawLine;
 
 static jmethodID id_drawPoint;
 
 static jmethodID id_zoomImage;
 
 static jmethodID id_getScrW;
 static jmethodID id_getScrH;
 
void file_copy(char *srcFile,char *desFile);


void initJniId(JNIEnv * env, jobject obj);

int datasave[255];
/*
jobject imageres[255];
int imgpoint=0;
*/
typedef int(*main_t)();
typedef void(*timers_t)(int* data);
typedef void(*on_touch)(int action,float x,float y,int pointerIndex,int pointerCount
			,float pointersX[],float pointersY[],int pointersId[]);


timers_t timer[255];

on_touch touchEvent_t;

int timerpoint=0;
inline getJniEnv()
{
   return mVmJniEnv;
}


int on_extract_entry(const char *filename, void *arg) {
    static int i = 0;
    int n = *(int *)arg;
    printf("Extracted: %s (%d of %d)\n", filename, ++i, n);

    return 0;
}



void native_main(JNIEnv *env, jobject obj,jstring path,jobject emuScreen){
	
	char *sopath=(char*)malloc(1024);
	sopath=jstringTostring(env,path);
	
	
	//system("su");
	/*
	int arg = 2;
zip_extract(sopath, tfile, on_extract_entry, &arg);
	*/
	//decompress_one_file(sopath,tfile);
	
	//unzipfile(sopath,tfile);
	char *tmf="/sdcard/lava/tmp/libgo.so";
	
	system("rm /data/data/as.mke.lavrun/files/librun.so");
	
	file_copy(tmf,sofile);
	
	system("rm -rf /sdcard/lava/tmp");
	
	    obj_emulator = (*env)->NewGlobalRef(env, obj);
		obj_emuScreen = (*env)->NewGlobalRef(env, emuScreen);
	
		mVmJniEnv = env;
	initJniId(env, obj);
	
	
}

#define MAX_POINTER_NUMBER 10
static float mPointersX[MAX_POINTER_NUMBER];
static float mPointersY[MAX_POINTER_NUMBER];
static int  mPointersID[MAX_POINTER_NUMBER];


jboolean touchEvent(JNIEnv* mEnv,jobject clazz,jint action,jfloat x,jfloat y,jint index,jint count
		,jfloatArray pointersX,jfloatArray pointersY,jintArray pointersId)
{

	(*mEnv)->GetFloatArrayRegion(mEnv,pointersX,0,count,mPointersX);
	(*mEnv)->GetFloatArrayRegion(mEnv,pointersY,0,count,mPointersY);
	(*mEnv)->GetIntArrayRegion(mEnv,pointersId,0,count,mPointersID);
	touchEvent_t(action,x,y,index,count,mPointersX,mPointersY,mPointersID);
	

		//	touchEvent_t((int)action,(int)x,(int)y,(int)pointerIndex,(int)pointerCount,(int)pointersX,(int)pointersY,(int)pointersId);
			
			return 1;
			}


void runTimerMethod(JNIEnv *env, jobject obj,jint point,jlong data){
	//void *bd=(void*)data;
	/*
	char *buf=(char*)malloc(1024);
	int a=(int)datasave[point];
	sprintf(buf,"data:%d",a);
	//emu_toast(buf);
	*/
	timer[point](datasave[point]);
	
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


int emu_getScrW(){
	
	JNIEnv *env=getJniEnv();
  
   return (*env)->CallIntMethod(env,obj_emuScreen,id_getScrW);

	
}

int emu_getScrH(){
	
	JNIEnv *env=getJniEnv();
  
   return (*env)->CallIntMethod(env,obj_emuScreen,id_getScrH);

	
}



void emu_drawPoint(int x,int y,int r,int g,int b){
	
	
	JNIEnv *env=getJniEnv();
  
   (*env)->CallVoidMethod(env,obj_emuScreen,id_drawPoint,(jint)x,(jint)y,(jint)r,(jint)g,(jint)b);

   
   }

void emu_drawLine(int x,int y,int x2,int y2,int r,int g,int b){
	
	
	JNIEnv *env=getJniEnv();
  
   (*env)->CallVoidMethod(env,obj_emuScreen,id_drawLine,(jint)x,(jint)y,(jint)x2,(jint)y2,(jint)r,(jint)g,(jint)b);

   
   }

int emu_zoomImage(int imgid,int w,int h){
	
	
	JNIEnv *env=getJniEnv();
  
 return   (*env)->CallIntMethod(env,obj_emuScreen,id_zoomImage,(jint)imgid,(jint)w,(jint)h);

   
   }


void emu_destroyImage(int id){
	JNIEnv *env=getJniEnv();
   
	(*env)->CallVoidMethod(env,obj_emuScreen,id_destroyImage,id);
	
}

void emu_deleteTimer(int id){
	JNIEnv *env=getJniEnv();
   
	(*env)->CallVoidMethod(env,obj_emulator,id_deleteTimer,id);
}

void emu_toast(char *bstr){
	
	JNIEnv *env=getJniEnv();
	//jstring ss=stoJstring(env,str);
	
	jbyteArray data = (*env)->NewByteArray(env, strlen(bstr));
(*env)->SetByteArrayRegion(env, data, 0, strlen(bstr), bstr);
   
	(*env)->CallVoidMethod(env,obj_emulator,id_toast,data);
	
}

void emu_drawImage(int imgid,int x,int y){
	
	JNIEnv *env=getJniEnv();
	//jstring ss=stoJstring(env,str);
	
	
	(*env)->CallVoidMethod(env,obj_emuScreen,id_drawImage,(jint)imgid,(jint)x,(jint)y);
}

int emu_loadImageForPath(char *bstr){
	JNIEnv *env=getJniEnv();
	//jstring ss=stoJstring(env,str);
	
	jbyteArray data = (*env)->NewByteArray(env, strlen(bstr));
(*env)->SetByteArrayRegion(env, data, 0, strlen(bstr), bstr);
   /*
	imageres[imgpoint]=(jobject)(*env)->CallLongMethod(env,obj_emulator,id_loadimageforpak,data);
	imgpoint++;
	return (imgpoint-1);
	*/
	
	
	return (*env)->CallIntMethod(env,obj_emuScreen,id_loadimageforext,data);
	
	
}



int emu_loadImageForData(char *bstr){
	JNIEnv *env=getJniEnv();
	//jstring ss=stoJstring(env,str);
	
	jbyteArray data = (*env)->NewByteArray(env, strlen(bstr));
(*env)->SetByteArrayRegion(env, data, 0, strlen(bstr), bstr);
   /*
	imageres[imgpoint]=(jobject)(*env)->CallLongMethod(env,obj_emulator,id_loadimageforpak,data);
	imgpoint++;
	return (imgpoint-1);
	*/
	
	
	(*env)->CallIntMethod(env,obj_emuScreen,id_loadimageforbyte,data);
	
	
}


int emu_loadImageForPak(char *bstr){
	
	JNIEnv *env=getJniEnv();
	//jstring ss=stoJstring(env,str);
	
	jbyteArray data = (*env)->NewByteArray(env, strlen(bstr));
(*env)->SetByteArrayRegion(env, data, 0, strlen(bstr), bstr);
   /*
	imageres[imgpoint]=(jobject)(*env)->CallLongMethod(env,obj_emulator,id_loadimageforpak,data);
	imgpoint++;
	return (imgpoint-1);
	*/
	
	
	return (*env)->CallIntMethod(env,obj_emuScreen,id_loadimageforpak,data);
	
}


//创建定时器
int emu_createTimer(char *bstr){
	
	
	JNIEnv *env=getJniEnv();
	jbyteArray data = (*env)->NewByteArray(env, strlen(bstr));
(*env)->SetByteArrayRegion(env, data, 0, strlen(bstr), bstr);
   
	return  (*env)->CallIntMethod(env,obj_emulator,id_createTimer,data);

}

int emu_startTimer(int id,void* data,long delay,long period){
	
	datasave[timerpoint-1]=10086;
	datasave[timerpoint-1]=data;
	JNIEnv *env=getJniEnv();
	
	
	return  (*env)->CallIntMethod(env,obj_emulator,id_startTimer,id,(jlong)datasave[timerpoint-1],(jlong)delay,(jlong)period);

	
}


jbyteArray geterror(JNIEnv * env, jobject obj){
	char *res=(char*)malloc(4096);
	res=dlerror();
	jbyteArray data = (*env)->NewByteArray(env, strlen(res));
(*env)->SetByteArrayRegion(env, data, 0, strlen(res), res);
   
	
	return data;
	
}
// 绘制颜色清屏
void emu_refs(int x,int y,int w,int h){
	
	
	JNIEnv *env=getJniEnv();
  
   (*env)->CallVoidMethod(env,obj_emuScreen,id_refs,(jint)x,(jint)y,(jint)w,(jint)h);

   
   }




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
	
	id_startTimer = (*env)->GetMethodID(env, cls, "N2J_startTimer", "(IJJJ)I");
	
	id_toast = (*env)->GetMethodID(env, cls, "N2J_Toast", "([B)V");
	
	id_deleteTimer=(*env)->GetMethodID(env,cls,"N2J_deleteTimer","(I)V");
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
	
	id_refs= (*env)->GetMethodID(env, cls, "N2J_refs", "(IIII)V");
    id_drawRGB = (*env)->GetMethodID(env, cls, "N2J_drawRGB", "(III)V");
	
	
	id_loadimageforpak= (*env)->GetMethodID(env, cls, "N2J_loadImageForPak", "([B)I");
	
	
	id_drawImage=(*env)->GetMethodID(env, cls, "N2J_drawImage", "(III)V");
	
	id_destroyImage=(*env)->GetMethodID(env,cls,"N2J_destroyImage","(I)V");
	
	
	id_drawLine=(*env)->GetMethodID(env,cls,"N2J_drawLine","(IIIIIII)V");
	
	id_drawPoint=(*env)->GetMethodID(env,cls,"N2J_drawPoint","(IIIII)V");
	
	id_zoomImage=(*env)->GetMethodID(env,cls,"N2J_zoomImage","(III)I");
	
	
	id_getScrW=(*env)->GetMethodID(env,cls,"N2J_getScrW","()I");
	
	id_getScrH=(*env)->GetMethodID(env,cls,"N2J_getScrH","()I");
	
	id_loadimageforext=(*env)->GetMethodID(env,cls,"N2J_loadImageForExt","([B)I");
	id_loadimageforbyte=(*env)->GetMethodID(env,cls,"N2J_loadImageForByte","([B)I");
	
	
	
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

	touchEvent_t=(on_touch)dlsym(handle,"onTouch");
	
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





// Demonstration of zlib utility functions
unsigned long file_size(char *filename)
{
   FILE *pFile = fopen(filename, "rb");
   fseek (pFile, 0, SEEK_END);
   unsigned long size = ftell(pFile);
   fclose (pFile);
   return size;
}


int decompress_one_file(char *infilename, char *outfilename)
{

   int num_read = 0;
   char buffer[128] = {0};

   gzFile infile = gzopen(infilename, "rb");
   FILE *outfile = fopen(outfilename, "wb");

   if (!infile || !outfile){
	   printf("fail uncompress\n");
        return -1;
   }

   while ((num_read = gzread(infile, buffer, sizeof(buffer))) > 0) {
      fwrite(buffer, 1, num_read, outfile);
      memset(buffer,0,128);
    }
   gzclose(infile);
   fclose(outfile);
   return 0;
}


int compress_one_file(char *infilename, char *outfilename)
{
    int num_read = 0;
   char inbuffer[128] = {0};
   unsigned long total_read = 0, total_wrote = 0;
   FILE *infile = fopen(infilename, "rb");
   gzFile outfile = gzopen(outfilename, "wb");
   if (!infile || !outfile){
        return -1;
   } 

   while ((num_read = fread(inbuffer, 1, sizeof(inbuffer), infile)) > 0) {
      total_read += num_read;
      gzwrite(outfile, inbuffer, num_read);
      memset(inbuffer,0,128);
   }
   fclose(infile);
   gzclose(outfile);
   printf("Read %ld bytes, Wrote %ld bytes,"
          "Compression factor %4.2f%%\n",
      total_read, file_size(outfilename),
      (1.0-file_size(outfilename)*1.0/total_read)*100.0);
   return 0;
}



void unzipfile(char *src,char *destfile){
	
	
	FILE* file;
	uLong flen;
	unsigned char* fbuf = NULL;
	uLong ulen;
	unsigned char* ubuf = NULL;
 
	/* 通过命令行参数将srcfile文件的数据解压缩后存放到dstfile文件中 */
	/*
	if(argc < 3)
	{
		printf("Usage: zudemo srcfile dstfile\n");
		return -1;
	}
 */
	if((file = fopen(src, "rb")) == NULL)
	{
		printf("Can\'t open %s!\n", src);
		return -1;
	}
	/* 装载源文件数据到缓冲区 */
	fread(&ulen, sizeof(uLong), 1, file);	/* 获取缓冲区大小 */
	fread(&flen, sizeof(uLong), 1, file);	/* 获取数据流大小 */
	if((fbuf = (unsigned char*)malloc(sizeof(unsigned char) * flen)) == NULL)
	{
		printf("No enough memory!\n");
		fclose(file);
		return -1;
	}
	fread(fbuf, sizeof(unsigned char), flen, file);
	/* 解压缩数据 */
	if((ubuf = (unsigned char*)malloc(sizeof(unsigned char) * ulen)) == NULL)
	{
		printf("No enough memory!\n");
		fclose(file);
		return -1;
	}
	if(uncompress(ubuf, &ulen, fbuf, flen) != Z_OK)
	{
		printf("Uncompress %s failed!\n", src);
		return -1;
	}
	fclose(file);
 
	if((file = fopen(destfile, "wb")) == NULL)
	{
		printf("Can\'t create %s!\n", destfile);
		return -1;
	}
	/* 保存解压缩后的数据到目标文件 */
	fwrite(ubuf, sizeof(unsigned char), ulen, file);
	fclose(file);
 
	free(fbuf);
	free(ubuf);
	
	
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




