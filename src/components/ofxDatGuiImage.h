//
//  ofxDatGuiImage.h
//  NervousStructureOF
//
//  Created by Cristobal Mendoza on 10/20/16.
//
//

#ifndef ofxDatGuiImage_h
#define ofxDatGuiImage_h

#include "ofxDatGuiComponent.h"
#include "ofMain.h"

class ofxDatGuiImage : public ofxDatGuiComponent {
	
public:
	
	ofxDatGuiImage(string label, int width, int height, ofImageType imageType) : ofxDatGuiComponent(label)
	{
		mType = ofxDatGuiType::BUTTON; //?
		iWidth = width;
		iHeight = height;
		this->imageType = imageType;
		image.allocate(width, height, imageType);
		setTheme(ofxDatGuiComponent::getTheme());
	}
	
	void setTheme(const ofxDatGuiTheme* theme)
	{
		setComponentStyle(theme);
		mStyle.stripe.color = theme->stripe.button;
		setWidth(theme->layout.width, theme->layout.labelWidth);
	}
	
	void setWidth(int width, float labelWidth = 1)
	{
		mStyle.height = (width * iHeight) / iWidth;
		ofxDatGuiComponent::setWidth(width, labelWidth);
		mLabel.width = mStyle.width;
		mLabel.rightAlignedXpos = mLabel.width - mLabel.margin;
		ofxDatGuiComponent::positionLabel();
	}
	
	void draw()
	{
		if (mVisible) {
			// anything that extends ofxDatGuiButton has the same rollover effect //
			ofPushStyle();
			if (mStyle.border.visible) drawBorder();
			ofFill();
			ofSetColor(255);
//			if (mFocused && mMouseDown){
//				ofSetColor(mStyle.color.onMouseDown, mStyle.opacity);
//			}   else if (mMouseOver){
//				ofSetColor(mStyle.color.onMouseOver, mStyle.opacity);
//			}   else{
//				ofSetColor(mStyle.color.background, mStyle.opacity);
//			}
//			ofDrawRectangle(x, y, mStyle.width, mStyle.height);
			
			//TODO: Thread safety
			if (doImageUpdate)
			{
				image.setFromPixels(tempPixels);
				doImageUpdate = false;
			}
			
			image.draw(x, y, mStyle.width, mStyle.height);
//			drawLabel();
			if (mStyle.stripe.visible) drawStripe();
			ofPopStyle();
		}
	}
	
	void updateImage(const ofPixels& pixels)
	{
		//TODO: Thread safety
		tempPixels = pixels;
		doImageUpdate = true;
	}
	
	ofEventListener updateEventListener;
	
	static ofxDatGuiImage* getInstance() { return new ofxDatGuiImage("X", 320, 340, OF_IMAGE_COLOR); }
	
protected:
	
	ofImage image;
	bool doImageUpdate = false;
	ofPixels tempPixels;
	int iWidth, iHeight;
	ofImageType imageType;
	void onMouseRelease(ofPoint m)
	{
		ofxDatGuiComponent::onFocusLost();
		ofxDatGuiComponent::onMouseRelease(m);
		// dispatch event out to main application //
//		if (buttonEventCallback != nullptr) {
//			ofxDatGuiButtonEvent e(this);
//			buttonEventCallback(e);
//		}   else{
//			ofxDatGuiLog::write(ofxDatGuiMsg::EVENT_HANDLER_NULL);
//		}
	}
	
};


#endif /* ofxDatGuiImage_h */
