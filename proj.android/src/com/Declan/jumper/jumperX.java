/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.Declan.jumper;

import cn.domob.android.ads.DomobAdEventListener;
import cn.domob.android.ads.DomobAdManager.ErrorCode;
import cn.domob.android.ads.DomobAdView;
import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup.LayoutParams;
import android.widget.RelativeLayout;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;


import com.umeng.socialize.controller.RequestType;
import com.umeng.socialize.controller.UMServiceFactory;
import com.umeng.socialize.controller.UMSocialService;
import com.umeng.socialize.media.UMImage;
import com.umeng.socialize.sso.*;

import android.os.Handler;

public class jumperX extends Cocos2dxActivity{
	
    
	public static Context STATIC_REF = null;
	//Domob Ad
    public static final String PUBLISHER_ID = "56OJzBMIuNL1O0/fnr";  
    public static final String InlinePPID = "16TLmTcoApfFONUfiJAgu42z";
    public static final String InterstitialPPID = "16TLmTcoApfFONUfTQHb7r6k";
    private static  Handler mHandler;   
    public static RelativeLayout mAdContainer;
	DomobAdView mAdview320x50;
	
    /**
     * 友盟Social SDK实例，整个SDK的Controller
     */
    private static UMSocialService mController = null;
    private static Activity mActivity = null;
    private static String shareText = null;

    
	@Override
	public void onCreate(Bundle savedInstanceState) {
	    super.onCreate(savedInstanceState);
	    
	    STATIC_REF = this;
	    mActivity = this;
	    
	    mController = UMServiceFactory.getUMSocialService(
                "com.umeng.share", RequestType.SOCIAL);
	    
	    mHandler = new Handler();
	    
	    mAdview320x50 = new DomobAdView(this, PUBLISHER_ID, InlinePPID, DomobAdView.INLINE_SIZE_320X50);
		mAdview320x50.setKeyword("game");
		
	    mAdContainer = new RelativeLayout(this);
        RelativeLayout.LayoutParams mAdContainerParams = new RelativeLayout.LayoutParams(
                RelativeLayout.LayoutParams.FILL_PARENT,
                RelativeLayout.LayoutParams.FILL_PARENT);
        RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(
                RelativeLayout.LayoutParams.FILL_PARENT,
                RelativeLayout.LayoutParams.WRAP_CONTENT);
        layoutParams.addRule(RelativeLayout.ALIGN_PARENT_TOP,
                RelativeLayout.TRUE);
        mAdContainer.addView(mAdview320x50, layoutParams);
                
        this.addContentView(mAdContainer, mAdContainerParams);
//	    setContentView(R.layout.main);
		

		mAdview320x50.setAdEventListener(new DomobAdEventListener() {
						
			@Override
			public void onDomobAdReturned(DomobAdView adView) {
				Log.i("DomobSDKDemo", "onDomobAdReturned");				
			}

			@Override
			public void onDomobAdOverlayPresented(DomobAdView adView) {
				Log.i("DomobSDKDemo", "overlayPresented");
			}

			@Override
			public void onDomobAdOverlayDismissed(DomobAdView adView) {
				Log.i("DomobSDKDemo", "Overrided be dismissed");				
			}

			@Override
			public void onDomobAdClicked(DomobAdView arg0) {
				Log.i("DomobSDKDemo", "onDomobAdClicked");				
			}

			@Override
			public void onDomobAdFailed(DomobAdView arg0, ErrorCode arg1) {
				Log.i("DomobSDKDemo", "onDomobAdFailed");				
			}

			@Override
			public void onDomobLeaveApplication(DomobAdView arg0) {
				Log.i("DomobSDKDemo", "onDomobLeaveApplication");				
			}

			@Override
			public Context onDomobAdRequiresCurrentContext() {
				return jumperX.this;
			}
		});
		RelativeLayout.LayoutParams layout=new RelativeLayout.LayoutParams(LayoutParams.WRAP_CONTENT,LayoutParams.WRAP_CONTENT);
		layout.addRule(RelativeLayout.CENTER_HORIZONTAL);
		mAdview320x50.setLayoutParams(layout);
		
	}
	
	private static Runnable showMyAdi = new Runnable() {    
	    public void run() { 
	    	if (jumperX.mAdContainer != null)
	    		jumperX.mAdContainer.setVisibility(View.VISIBLE);
	    }    
	};
	
	private static Runnable hideMyAdi = new Runnable() {
		public void run() {
			if (jumperX.mAdContainer != null)
				jumperX.mAdContainer.setVisibility(View.INVISIBLE);
		}
	};
	
	public static void showMyAd() {
		if (showMyAdi != null && mHandler != null)
			mHandler.post(showMyAdi);   
	}
	
	public static void hideMyAd() {
		if (hideMyAdi != null && mHandler != null)
			mHandler.post(hideMyAdi);
	}
	
	public static Context getContext(){
	    return STATIC_REF;
	}
	
    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// jumperX should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	return glSurfaceView;
    }
    
    /**
     * @Title:  openShareBoard
     * @Description:
     *       调用友盟的openShare方法， 打开分享平台选择面板
     * @throws
     */
    public static void openShareBoard(String text) {
    	shareText = text;
        mHandler.postDelayed(new Runnable() {

            @Override
            public void run() {
                if (mActivity != null) {
                    /**
                     *   设置新浪微博、QQ空间、腾讯微博的Handler,进行SSO授权
                     *
                     *   注意 ： 新浪平台支持SSO则需要把友盟提供的com.sina.sso拷进src里面，
                     *      需要将友盟提供的libs、res文件拷贝到您的工程对应的目录里面.
                     */
                    mController.getConfig().setSsoHandler(new SinaSsoHandler());
                    mController.getConfig().setSsoHandler(new QZoneSsoHandler(mActivity));
                    mController.getConfig().setSsoHandler(new TencentWBSsoHandler());
                    mController.setShareContent(shareText);
                    mController.setShareMedia(new UMImage(mActivity, R.drawable.icon));
                    // 打开友盟的分享平台选择面板
                    mController.openShare(mActivity, false);
                }
            }
        }, 100);
    }

    static {
        System.loadLibrary("cocos2dcpp");
    }     

}
