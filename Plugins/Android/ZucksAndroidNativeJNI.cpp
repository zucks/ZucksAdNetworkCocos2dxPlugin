//
//  ZucksAndroidNativeJNI.cpp
//  ZucksAdNetworkCocos2dxPlugin
//
//  Copyright (C) 2017 Zucks, Inc.
//
//

#include "ZucksAndroidNativeJNI.h"

using namespace zucks_plugin::internal;

#pragma mark - Constructor / Destructor
ZucksAndroidNativeJNI::ZucksAndroidNativeJNI()
{
}

ZucksAndroidNativeJNI::~ZucksAndroidNativeJNI()
{
}

void ZucksAndroidNativeJNI::callJNI(const std::function<void (JNIEnv* env)> &callback)
{
    JavaVM* jvm = JniHelper::getJavaVM();
    JNIEnv *env;
    int status;
    bool isAttached = false;

    status = jvm->GetEnv((void **) &env, JNI_VERSION_1_6);

    if(status < 0) {
        status = jvm->AttachCurrentThread(&env, NULL);
        if(status < 0) {
            return;
        }
        isAttached = true;
    }

    callback(env);

    if(isAttached) {
        jvm->DetachCurrentThread();
    }
}
