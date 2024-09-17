#include <jni.h>
#include <iostream>
#include <string>
#include "TestJNI.h"

JNIEXPORT jstring JNICALL Java_TestJNI_NativeMessage(JNIEnv *env, jobject jObj, jstring jMsg) {
    std::string message = std::string(env->GetStringUTFChars(jMsg, NULL));
    std::cout << message << " <= from NativeMessage()\n";

    std::string ret = "Return Message from NativeMessage << hello by fa1c4\n";
    return env->NewStringUTF(ret.c_str());
}
