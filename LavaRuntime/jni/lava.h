#include <jni.h>

void native_main(JNIEnv *env, jobject obj,jstring path,jobject screen);
jbyteArray native_result(JNIEnv *env,jobject obj);
jbyteArray geterror(JNIEnv *env, jobject obj);
void runTimerMethod(JNIEnv *env, jobject obj,jint point,jlong data);
int registerTimer(JNIEnv *env, jobject obj,jstring str);

