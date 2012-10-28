//
//  GLView.h
//  HelloArrow
//
//  Created by shin on 12-10-28.
//  Copyright (c) 2012年 Indie Developer. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <OpenGLES/EAGL.h>
#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

#import "IRenderingEngine.h"

@interface GLView : UIView
{
    EAGLContext         *m_context;
    IRenderingEngine    *m_renderingEngine;
    float               m_timestamp;
}

- (void)drawView:(CADisplayLink *)displayLink;
- (void)didRotate:(NSNotification *)notification;

@end
