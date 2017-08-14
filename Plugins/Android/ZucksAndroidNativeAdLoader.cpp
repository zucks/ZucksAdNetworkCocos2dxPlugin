//
//  ZucksAndroidNativeAdLoader.cpp
//  ZucksAdNetworkCocos2dxPlugin
//
//  Copyright (C) 2017 Zucks, Inc.
//
//

#include "ZucksAndroidNativeAdLoader.h"

using namespace zucks_plugin;
using namespace zucks_plugin::internal;

#define CLASS_NAME "net/zucks/nativead/NativeAdLoader"
#define METHOD_NAME_CREATE "createNativeAdLoader"
#define METHOD_NAME_LOAD "loadAd"

#pragma mark - Constructor / Destructor

std::function<void (ZucksNativeAd* nativeAd, int* errorCode, std::string errorMessage)> nativeCallback;

ZucksAndroidNativeAdLoader::ZucksAndroidNativeAdLoader(const std::string frameId, const std::string bridgeVersion, const std::string cocos2dVersion):IZucksNativeAdLoader(frameId)
{
    std::function<void (JNIEnv* env)> callback_ = [=](JNIEnv* env) {
        jclass cls = env->FindClass(CLASS_NAME);

        if (cls == NULL) {
            return;
        }

        jmethodID cns = env->GetMethodID(cls, "<init>", "()V");
        if (cns == NULL) {
            return;
        }

        jobject localObj = env->NewObject(cls, cns);
        if (localObj == NULL) {
            return;
        }
        m_nativeClient = env->NewGlobalRef(localObj);
        if (m_nativeClient == NULL) {
            return;
        }

        jmethodID mid = env->GetMethodID(cls, METHOD_NAME_CREATE, "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
        if (mid != NULL) {
            jstring stringFrameId = env->NewStringUTF(frameId.c_str());
            jstring stringCocos2dVersion = env->NewStringUTF(cocos2dVersion.c_str());
            jstring stringBridgeVersion = env->NewStringUTF(bridgeVersion.c_str());
            env->CallVoidMethod(m_nativeClient, mid, stringFrameId, stringCocos2dVersion, stringBridgeVersion);
        }
    };
    this->callJNI(callback_);
}

ZucksAndroidNativeAdLoader::~ZucksAndroidNativeAdLoader()
{
    std::function<void (JNIEnv* env)> callback_ = [=](JNIEnv* env) {
        if (m_nativeClient != NULL) {
            env->DeleteGlobalRef(m_nativeClient);
        }
    };
    this->callJNI(callback_);
}

#pragma mark - Internal
std::string convertToCString(const char *charText)
{
    if (charText != NULL){
        return std::string(charText);
    }
    return "";
}

void createNativeAd(JNIEnv* env, jobject javaNativeAd, std::function<void (ZucksNativeAd* nativeAd)> &callback)
{
    const char *imageSrc = NULL;
    const char *bodyText = NULL;
    const char *title = NULL;
    const char *productName = NULL;
    const char *advertiserName = NULL;
    const char *linkButtonText = NULL;
    const char *landingUrl = NULL;

    jclass cls = env->FindClass("net/zucks/nativead/NativeAd");
    if (cls == NULL) {
        return;
    }

    if (javaNativeAd == NULL) {
        return;
    }

    jfieldID fid_imageSrc = env->GetFieldID(cls, "imageSrc", "Ljava/lang/String;");
    jfieldID fid_bodyText = env->GetFieldID(cls, "bodyText", "Ljava/lang/String;");
    jfieldID fid_title = env->GetFieldID(cls, "title", "Ljava/lang/String;");
    jfieldID fid_productName = env->GetFieldID(cls, "productName", "Ljava/lang/String;");
    jfieldID fid_advertiserName = env->GetFieldID(cls, "advertiserName", "Ljava/lang/String;");
    jfieldID fid_linkButtonText = env->GetFieldID(cls, "linkButtonText", "Ljava/lang/String;");
    jfieldID fid_landingUrl = env->GetFieldID(cls, "landingUrl", "Ljava/lang/String;");

    ZucksNativeAd* nativeAd = new ZucksNativeAd();
    CC_SAFE_RETAIN(nativeAd);

    if (fid_imageSrc != NULL) {
        jstring jstr = (jstring)env->GetObjectField(javaNativeAd, fid_imageSrc);
        if (jstr != NULL) {
            imageSrc = env->GetStringUTFChars(jstr, NULL);
            nativeAd->setImageUrl(convertToCString(imageSrc));
            env->ReleaseStringUTFChars(jstr, imageSrc);
        }
    }

    if (fid_bodyText != NULL) {
        jstring jstr = (jstring)env->GetObjectField(javaNativeAd, fid_bodyText);
        if (jstr != NULL) {
            bodyText = env->GetStringUTFChars(jstr, NULL);
            nativeAd->setBodyText(convertToCString(bodyText));
            env->ReleaseStringUTFChars(jstr, bodyText);
        }
    }

    if (fid_title != NULL) {
        jstring jstr = (jstring)env->GetObjectField(javaNativeAd, fid_title);
        if (jstr != NULL) {
            title = env->GetStringUTFChars(jstr, NULL);
            nativeAd->setTitle(convertToCString(title));
            env->ReleaseStringUTFChars(jstr, title);
        }
    }

    if (fid_productName != NULL) {
        jstring jstr = (jstring)env->GetObjectField(javaNativeAd, fid_productName);
        if (jstr != NULL) {
            productName = env->GetStringUTFChars(jstr, NULL);
            nativeAd->setProductName(convertToCString(productName));
            env->ReleaseStringUTFChars(jstr, productName);
        }
    }

    if (fid_advertiserName != NULL) {
        jstring jstr = (jstring)env->GetObjectField(javaNativeAd, fid_advertiserName);
        if (jstr != NULL) {
            advertiserName = env->GetStringUTFChars(jstr, NULL);
            nativeAd->setAdvertiserName(convertToCString(advertiserName));
            env->ReleaseStringUTFChars(jstr, advertiserName);
        }
    }

    if (fid_linkButtonText != NULL) {
        jstring jstr = (jstring)env->GetObjectField(javaNativeAd, fid_linkButtonText);
        if (jstr != NULL) {
            linkButtonText = env->GetStringUTFChars(jstr, NULL);
            nativeAd->setLinkButtonText(convertToCString(linkButtonText));
            env->ReleaseStringUTFChars(jstr, linkButtonText);
        }
    }

    if (fid_landingUrl != NULL) {
        jstring jstr = (jstring)env->GetObjectField(javaNativeAd, fid_landingUrl);
        if (jstr != NULL) {
            landingUrl = env->GetStringUTFChars(jstr, NULL);
            nativeAd->setLandingUrl(convertToCString(landingUrl));
            env->ReleaseStringUTFChars(jstr, landingUrl);
        }
    }

    callback(nativeAd);
}

void loadAdFailed(JNIEnv* env, jint jerrorCode, jstring jerrorMessage, std::function<void (int errorInt, std::string message)> &callback)
{
    const char *errorMessage = NULL;
    jstring messageObj = jerrorMessage;
    if (messageObj) {
        errorMessage = env->GetStringUTFChars(messageObj, NULL);
    }

    if (callback) {
        callback(jerrorCode, std::string(errorMessage));
    }

    if (messageObj != NULL && errorMessage != NULL){
        env->ReleaseStringUTFChars(messageObj, errorMessage);
    }
}

#pragma mark - loadAd
void ZucksAndroidNativeAdLoader::loadAd(const std::function<void (ZucksNativeAd*, int*, std::string)> &callback)
{
    nativeCallback = callback;

    std::function<void (JNIEnv* env)> callback_ = [=](JNIEnv* env) {
        jclass cls = env->FindClass(CLASS_NAME);

        if (cls == NULL) {
            return;
        }

        if (m_nativeClient == NULL) {
            return;
        }

        jmethodID mid = env->GetMethodID(cls, METHOD_NAME_LOAD, "()V");
        if (mid != NULL) {
            env->CallVoidMethod(m_nativeClient, mid);
        }
    };
    this->callJNI(callback_);
}

#pragma mark - JNICALL
extern "C"
{
    JNIEXPORT void JNICALL Java_net_zucks_nativead_NativeAdLoader_getNativeAdConnectorJNICallBack(JNIEnv* env, jobject thiz, jobject javaNativeAd) {
        std::function<void (ZucksNativeAd* nativeAd)> callback_ = [=](ZucksNativeAd* nativeAd) {
            nativeCallback(nativeAd, nullptr, "");
        };
        if (!nativeCallback) {
            return;
        }
        createNativeAd(env, javaNativeAd, callback_);
    }

	JNIEXPORT void JNICALL Java_net_zucks_nativead_NativeAdLoader_loadAdFailedJNICallBack(JNIEnv* env, jobject thiz, jint errorCode, jstring errorMessage){
        std::function<void (int errorInt, std::string message)> callback_ = [=](int errorInt, std::string message) {
            nativeCallback(nullptr, &errorInt, message);
        };
        if (!nativeCallback) {
            return;
        }
        loadAdFailed(env, errorCode, errorMessage, callback_);
	}
}
