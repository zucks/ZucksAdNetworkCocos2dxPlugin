//
//  ZucksNativeAdLoader.h
//  ZucksAdNetworkCocos2dxPlugin
//
//  Copyright (C) 2017 Zucks, Inc.
//
//

#ifndef ZucksNativeAdLoader_h
#define ZucksNativeAdLoader_h

#include "cocos2d.h"
#include "IZucksNativeAdLoader.h"
#include "ZucksNativeAd.h"

USING_NS_CC;

namespace zucks_plugin
{
  typedef enum {
    ZUCKS_SUCCESS_LOAD_AD = 0,
    ZUCKS_ERRORTYPE_OFFLINE = 1,
    ZUCKS_ERRORTYPE_FRAMEID_UNDEFINED = 2,
    ZUCKS_ERRORTYPE_AD_OUT_OF_STOCK = 3,
    ZUCKS_ERRORTYPE_OTHER = 4
  } ZucksNativeLoadResultCode;
  
  class ZucksNativeAdLoader : public cocos2d::Ref
  {
  public:
    ZucksNativeAdLoader(std::string frameId);
    virtual ~ZucksNativeAdLoader();
    
    static zucks_plugin::ZucksNativeAdLoader* create(std::string apiKey, std::string spotID);
    void loadAd(const std::function<void (zucks_plugin::ZucksNativeAd*, ZucksNativeLoadResultCode, std::string)> &callback);
    
  private:
    void initialize(const std::string apiKey, const std::string spotID);
    zucks_plugin::internal::IZucksNativeAdLoader* m_loader;
  };
}

#endif /* ZucksNativeAdLoader_h */
