package net.zucks.nativead;

import android.app.Activity;

import net.zucks.exception.FrameIdNotFoundException;
import net.zucks.exception.NetworkNotFoundException;
import net.zucks.internal.common.Platform;

import org.cocos2dx.lib.Cocos2dxActivity;

public class NativeAdLoader {

    public static native void getNativeAdConnectorJNICallBack(final NativeAd nativeAd);

    public static native void loadAdFailedJNICallBack(final int errorCode, final String errorMessage);

    private String frameId;
    private String platformVersion;
    private String bridgeVersion;
    private NativeAdClient client;

    public void createNativeAdLoader(final String frameId, final String platformVersion, final String bridgeVersion) {
        final Activity activity = (Activity) Cocos2dxActivity.getContext();
        this.frameId = frameId;
        this.platformVersion = platformVersion;
        this.bridgeVersion = bridgeVersion;
        this.client = new NativeAdClient(activity, this.frameId, Platform.COCOS2DX, this.platformVersion, this.bridgeVersion, new NativeAdListener() {
            @Override
            public void onLoadAd(NativeAd nativeAd) {
                getNativeAdConnectorJNICallBack(nativeAd);
            }

            @Override
            public void onNotExistAd() {
                // ZucksNativeAdLoader.h/ZUCKS_ERRORTYPE_AD_OUT_OF_STOCK
                loadAdFailedJNICallBack(3, "Native Code Error: There is no advertisement.");
            }

            @Override
            public void onFailure(Exception e) {
                if (e instanceof NetworkNotFoundException) {
                    // ZucksNativeAdLoader.h/ZUCKS_ERRORTYPE_OFFLINE
                    loadAdFailedJNICallBack(1, "Native Code Error: " + e.getMessage());
                } else if (e instanceof FrameIdNotFoundException) {
                    // ZucksNativeAdLoader.h/ZUCKS_ERRORTYPE_FRAMEID_UNDEFINED
                    loadAdFailedJNICallBack(2, "Native Code Error: " + e.getMessage());
                } else {
                    // ZucksNativeAdLoader.h/ZUCKS_ERRORTYPE_OTHER
                    loadAdFailedJNICallBack(4, "Native Code Error: " + e.getMessage());
                }
            }
        });
    }

    public void loadAd() {
        if (client == null) {
            return;
        }
        client.load();
    }
}
