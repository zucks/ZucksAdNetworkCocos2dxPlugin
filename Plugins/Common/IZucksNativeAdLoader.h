//
//  IZucksNativeAdLoader.h
//  ZucksAdNetworkCocos2dxPlugin
//
//  Copyright (C) 2017 Zucks, Inc.
//
//

#ifndef IZucksNativeAdLoader_h
#define IZucksNativeAdLoader_h


#include "ZucksNativeAd.h"

namespace zucks_plugin
{
  namespace internal
  {
    class IZucksNativeAdLoader : public cocos2d::Ref
    {
    protected:
      IZucksNativeAdLoader(const std::string frameId){}
    public:
      virtual ~IZucksNativeAdLoader(){}
      virtual void loadAd(const std::function<void (ZucksNativeAd*, int*, std::string)> &callback) = 0;
    };
  }
}


#endif /* IZucksNativeAdLoader_h */
