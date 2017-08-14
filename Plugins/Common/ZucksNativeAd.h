//
//  ZucksNativeAd.h
//  ZucksAdNetworkCocos2dxPlugin
//
//  Copyright (C) 2017 Zucks, Inc.
//
//

#ifndef ZucksNativeAd_h
#define ZucksNativeAd_h

#include "cocos2d.h"

namespace zucks_plugin
{
  class ZucksNativeAd : public cocos2d::Ref
  {
  public:
    ZucksNativeAd(){}
    
    ~ZucksNativeAd();
    
    void setImageUrl(std::string text){m_imageUrl = text;}
    std::string getImageUrl(){return m_imageUrl;}
    
    void setLandingUrl(std::string text){m_landingUrl = text;}
    std::string getLandingUrl(){return m_landingUrl;}
    
    void setTitle(std::string text){m_title = text;}
    std::string getTitle(){return m_title;}
    
    void setBodyText(std::string text){m_bodyText = text;}
    std::string getBodyText(){return m_bodyText;}
    
    void setProductName(std::string text){m_productName = text;}
    std::string getProductName(){return m_productName;}
    
    void setAdvertiserName(std::string text){m_advertiserName = text;}
    std::string getAdvertiserName(){return m_advertiserName;}
    
    void setLinkButtonText(std::string text){m_linkButtonText = text;}
    std::string getLinkButtonText(){return m_linkButtonText;}

  private:
    
    std::string m_imageUrl;
    std::string m_landingUrl;
    std::string m_title;
    std::string m_bodyText;
    std::string m_productName;
    std::string m_advertiserName;
    std::string m_linkButtonText;
  };
}

#endif /* ZucksNativeAd_h */
