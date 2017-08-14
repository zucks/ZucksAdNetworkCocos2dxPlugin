//
//  ZucksiOSNativeAdLoader.h
//  ZucksAdNetworkCocos2dxPlugin
//
//  Copyright (C) 2017 Zucks, Inc.
//
//

#ifndef ZucksiOSNativeAdLoader_h
#define ZucksiOSNativeAdLoader_h

#include "cocos2d.h"
#include "IZucksNativeAdLoader.h"

USING_NS_CC;

namespace zucks_plugin
{
  namespace internal
  {
    class ZucksiOSNativeAdLoader : public IZucksNativeAdLoader
    {
    public:
      ZucksiOSNativeAdLoader(std::string frameId,std::string bridgeVersion, std::string platformVersion);
      ~ZucksiOSNativeAdLoader();
      virtual void loadAd(const std::function<void (ZucksNativeAd*, int*, std::string)> &callback) override;

    private:
      std::string m_frameId;
      std::string m_bridgeVersion;
      std::string m_platformVersion;
    };
  }
}

#endif /* ZucksiOSNativeAdLoader_h */
