#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_lyndon_portfolio_1app_1java_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "";
    return env->NewStringUTF(hello.c_str());
}
