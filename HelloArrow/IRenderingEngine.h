//
//  IRenderingEngine.h
//  HelloArrow
//
//  Created by shin on 12-10-28.
//  Copyright (c) 2012年 Indie Developer. All rights reserved.
//

#ifndef HelloArrow_IRenderingEngine_h
#define HelloArrow_IRenderingEngine_h

enum DeviceOrientation {
    DeviceOrientationUnknown,
    DeviceOrientationPortrait,
    DeviceOrientationPortraitUpsideDown,
    DeviceOrientationLandscapeLeft,
    DeviceOrientationLandscapeRight,
    DeviceOrientationFaceUp,
    DeviceOrientationFaceDown,
};

struct IRenderingEngine *CreateRender1();

struct IRenderingEngine {
    virtual void Initialize(int width,int height) = 0;
    virtual void Render() const = 0;
    virtual void UpdateAniamtion(float timeStep) = 0;
    virtual void OnRotate(DeviceOrientation newOrientation) = 0;
    virtual ~IRenderingEngine(){}
};

#endif
