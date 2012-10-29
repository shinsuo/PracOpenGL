//
//  IRenderingEngine1.h
//  HelloArrow
//
//  Created by shin on 12-10-29.
//  Copyright (c) 2012年 Indie Developer. All rights reserved.
//

#ifndef __HelloArrow__IRenderingEngine1__
#define __HelloArrow__IRenderingEngine1__


enum DeviceOrientation {
    DeviceOrientationUnknown,
    DeviceOrientationPortrait,
    DeviceOrientationPortraitUpsideDown,
    DeviceOrientationLandscapeLeft,
    DeviceOrientationLandscapeRight,
    DeviceOrientationFaceUp,
    DeviceOrientationFaceDown,
};

class IRenderingEngine {
    
public:
    virtual void Initialize(int width,int height) = 0;
    virtual void Render() const = 0;
    virtual void UpdateAniamtion(float timeStep) = 0;
    virtual void OnRotate(DeviceOrientation newOrientation) = 0;
    virtual ~IRenderingEngine(){}
    
};

IRenderingEngine *CreateRender1();
IRenderingEngine *CreateRender2();

#endif /* defined(__HelloArrow__IRenderingEngine1__) */
