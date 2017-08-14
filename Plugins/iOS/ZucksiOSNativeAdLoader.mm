//
//  ZucksiOSNativeAdLoader.mm
//  ZucksAdNetworkCocos2dxPlugin
//
//  Copyright (C) 2017 Zucks, Inc.
//
//

#import <ZucksAdNetworkSDK/ZADNSdk.h>
#import <ZucksAdNetworkSDK/ZADNPlatform.h>
#import <ZucksAdNetworkSDK/ZADNNativeAdLoader.h>
#import <ZucksAdNetworkSDK/ZADNNativeAd.h>
#include "ZucksiOSNativeAdLoader.h"
#include "ZucksNativeAd.h"

using namespace zucks_plugin;
using namespace zucks_plugin::internal;

#pragma mark - Constructor / Destructor
ZucksiOSNativeAdLoader::ZucksiOSNativeAdLoader(const std::string frameId,const std::string bridgeVersion,const std::string platformVersion): IZucksNativeAdLoader(frameId)
{
  m_frameId = frameId;
  m_bridgeVersion = bridgeVersion;
  m_platformVersion = platformVersion;
}

ZucksiOSNativeAdLoader::~ZucksiOSNativeAdLoader()
{
}


std::string convertToString(NSString *nsString)
{
  if ([nsString length] > 0) {
    return [nsString UTF8String];
  }
  return "";
}


ZucksNativeAd *createZucksNativeAd(ZADNNativeAd *zucksNative)
{
  ZucksNativeAd *nativeAd = new ZucksNativeAd();
  nativeAd->autorelease();
  CC_SAFE_RETAIN(nativeAd);

  NSURL *landingUrl = [[zucksNative performSelector:@selector(adInfo)] performSelector:@selector(landingUrl)];
  nativeAd->setImageUrl(convertToString(zucksNative.imageUrl.absoluteString));
  nativeAd->setLandingUrl(convertToString(landingUrl.absoluteString));
  nativeAd->setTitle(convertToString(zucksNative.title));
  nativeAd->setBodyText(convertToString(zucksNative.bodyText));
  nativeAd->setProductName(convertToString(zucksNative.productName));
  nativeAd->setAdvertiserName(convertToString(zucksNative.advertiserName));
  nativeAd->setLinkButtonText(convertToString(zucksNative.linkButtonText));
  return nativeAd;
}


#pragma mark - loadAd
void ZucksiOSNativeAdLoader::loadAd(const std::function<void(ZucksNativeAd *, int *, std::string)> &callback)
{
  std::function<void(ZucksNativeAd * nativeAd, int *errorCode, std::string errorMessage)> callback_ = callback;

  NSString *frameId = [NSString stringWithUTF8String:m_frameId.c_str()];
  ZADNNativeAdLoader *loader = [[ZADNNativeAdLoader alloc] initWithFrameId:frameId];
  
  loader.zucksPlatform.bridgeVersion = [NSString stringWithFormat:@"%s", m_bridgeVersion.c_str()];
  loader.zucksPlatform.zucksPlatformVersion = [NSString stringWithFormat:@"%s", m_platformVersion.c_str()];
  loader.zucksPlatform.zucksPlatformType = ZADNPlatformTypeCocos2dx;
  
  [loader loadAdWithCompletionHandler:^(ZADNNativeAd * _Nullable nativeAd, NSError * _Nullable error) {
    if (nativeAd) {
      ZucksNativeAd *nativeAd_ = createZucksNativeAd(nativeAd);

      if (callback_) {
        callback_(nativeAd_, nullptr, "");
      }
    } else {
      if (error) {
        NSNumber *errorNumber = [NSNumber numberWithInteger:error.code];
        int errorCode = [errorNumber intValue];
        if (callback_) {
          callback_(nullptr, &errorCode, [error.description UTF8String]);
        }
      }
    }
  }];
  [loader release];
}


