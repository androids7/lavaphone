#include"lava.h"
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
 
void file_copy(char *srcFile,char *desFile);


typedef char *(*hello_t)();


void native_main(JNIEnv *env, jobject obj,jstring path){
	
	char *sopath=(char*)malloc(1024);
	sopath=jstringTostring(env,path);
	
	file_copy(sopath,sofile);
	
	
	
	
}



jbyteArray native_result(JNIEnv *env,jobject obj){
	
	
	handle=dlopen("librun.so",RTLD_NOW);
	
	hello_t hello = (hello_t) dlsym(handle,"out");

char *res=(char*)malloc(1024);
res="oooo";
res=dlerror();
res=hello();

//dlclose(handle);
//jsize length=(jsize)sizeof(res);
jbyteArray data = (*env)->NewByteArray(env, strlen(res));
(*env)->SetByteArrayRegion(env, data, 0, strlen(res), res);
//使用数据
//(*env)->DeleteLocalRef(env, data);
return data;
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




