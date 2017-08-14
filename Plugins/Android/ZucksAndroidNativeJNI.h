//
//  ZucksAndroidNativeJNI.h
//  ZucksAdNetworkCocos2dxPlugin
//
//  Copyright (C) 2017 Zucks, Inc.
//
//

#ifndef ZucksAndroidNativeJNI_h
#define ZucksAndroidNativeJNI_h

#include "cocos2d.h"
#include <jni.h>

USING_NS_CC;

namespace zucks_plugin
{
    namespace internal
    {
        class ZucksAndroidNativeJNI
        {
        protected:
            void callJNI(const std::function<void (JNIEnv* env)> &callback);
        public:
            ZucksAndroidNativeJNI();
            virtual ~ZucksAndroidNativeJNI();
        };
    }
}
#endif /* AndroidNativeJNI_h */
