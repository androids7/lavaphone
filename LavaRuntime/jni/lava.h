#include <jni.h>

void native_main(JNIEnv *env, jobject obj,jstring path,jobject screen);
//jbyteArray
int native_result(JNIEnv *env,jobject obj);

void runTimerMethod(JNIEnv *env, jobject obj,jint point);
int registerTimer(JNIEnv *env, jobject obj,jstring str,jlong time);
