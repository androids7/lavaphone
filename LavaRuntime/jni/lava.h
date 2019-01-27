#include <jni.h>

void native_main(JNIEnv *env, jobject obj,jstring path,jobject screen);
jbyteArray native_result(JNIEnv *env,jobject obj);
jbyteArray geterror(JNIEnv *env, jobject obj);
void runTimerMethod(JNIEnv *env, jobject obj,jint point,jlong data);
int registerTimer(JNIEnv *env, jobject obj,jstring str);
jboolean touchEvent(JNIEnv* mEnv,jclass clazz,jint action,jfloat x,jfloat y,jint index,jint count
		,jfloatArray pointersX,jfloatArray pointersY,jintArray pointersId);
