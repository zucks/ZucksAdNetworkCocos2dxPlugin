//
//  ZucksAndroidNativeAdLoader.h
//  ZucksAdNetworkCocos2dxPlugin
//
//  Copyright (C) 2017 Zucks, Inc.
//
//

#ifndef ZucksAndroidNativeAdLoader_h
#define ZucksAndroidNativeAdLoader_h

#include "cocos2d.h"
#include "ZucksAndroidNativeJNI.h"
#include "Plugins/Common/IZucksNativeAdLoader.h"
#include <jni.h>

USING_NS_CC;

namespace zucks_plugin
{
    namespace internal
    {
        class ZucksAndroidNativeAdLoader : public IZucksNativeAdLoader, public ZucksAndroidNativeJNI
        {
        private:
            jobject m_nativeClient;
        public:
            ZucksAndroidNativeAdLoader(std::string frameId, std::string bridgeVersion, std::string cocos2dVersion);
            ~ZucksAndroidNativeAdLoader();
            virtual void loadAd(const std::function<void (ZucksNativeAd*, int*, std::string)> &callback) override;
        };
    }
}
#endif /* ZucksAndroidNativeAdLoader_h */
