//
//  ZucksNativeAdLoader.cpp
//  ZucksAdNetworkCocos2dxPlugin
//
//  Copyright (C) 2017 Zucks, Inc.
//
//

#include "ZucksNativeAdLoader.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "ZucksiOSNativeAdLoader.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "Plugins/Android/ZucksAndroidNativeAdLoader.h"
#endif

using namespace zucks_plugin;
using namespace zucks_plugin::internal;

static const char* BRIDGE_VERSION = "1.0.0";
static const char* PLATFORM_VERSION = cocos2dVersion();

#pragma mark - Constructor / Destructor
ZucksNativeAdLoader::ZucksNativeAdLoader(const std::string frameId)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  this->m_loader = new ZucksiOSNativeAdLoader(frameId, BRIDGE_VERSION, PLATFORM_VERSION);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
  this->m_loader = new ZucksAndroidNativeAdLoader(frameId, BRIDGE_VERSION, PLATFORM_VERSION);
#endif
}

ZucksNativeAdLoader::~ZucksNativeAdLoader()
{
  CC_SAFE_DELETE(m_loader);
}

#pragma mark - loadNativeAdClient
void ZucksNativeAdLoader::loadAd(const std::function<void(zucks_plugin::ZucksNativeAd *, ZucksNativeLoadResultCode, std::string)> &callback)
{
  this->m_loader->loadAd([=](ZucksNativeAd *ad, int *errorCode, std::string errorMessage) {
    if (ad) {
      callback(ad, ZUCKS_SUCCESS_LOAD_AD, "");
      CC_SAFE_RELEASE(ad);
    } else {
      int errorResult = *errorCode;
      switch (errorResult) {
        case ZUCKS_ERRORTYPE_OFFLINE:
          callback(nullptr, ZUCKS_ERRORTYPE_OFFLINE, errorMessage);
          break;
        case ZUCKS_ERRORTYPE_FRAMEID_UNDEFINED:
          callback(nullptr, ZUCKS_ERRORTYPE_FRAMEID_UNDEFINED, errorMessage);
          break;
        case ZUCKS_ERRORTYPE_AD_OUT_OF_STOCK:
          callback(nullptr, ZUCKS_ERRORTYPE_AD_OUT_OF_STOCK, errorMessage);
          break;
        default:
          callback(nullptr, ZUCKS_ERRORTYPE_OTHER, errorMessage);
          break;
      }
    }
  });
}
