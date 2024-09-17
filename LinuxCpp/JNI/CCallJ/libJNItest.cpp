#include <jni.h>
#include <iostream>
#include <string>
#include "TestJNI.h"

JNIEXPORT jstring JNICALL Java_TestJNI_NativeMessage(JNIEnv *env, jobject jObj, jstring jMsg) {
    std::string message = std::string(env->GetStringUTFChars(jMsg, JNI_FALSE));
    std::cout << message << " <= from NativeMessage()" << std::endl;

    jclass thisClass = env->GetObjectClass(jObj);
    jmethodID mid = env->GetMethodID(thisClass, "setValue", "(Ljava/lang/String;)V");
    jstring msg = env->NewStringUTF("Hello From NativeMethod()");
    env->CallVoidMethod(jObj, mid, msg);

    jfieldID fid = env->GetFieldID(thisClass, "value", "Ljava/lang/String;");
    jstring val = (jstring)env->GetObjectField(jObj, fid);
    std::cout << std::string(env->GetStringUTFChars(val, JNI_FALSE)) << " <= NativeMethod()" << std::endl;

    std::string ret = "Return Message from NativeMessage << hello by fa1c4\n";
    return env->NewStringUTF(ret.c_str());
}
