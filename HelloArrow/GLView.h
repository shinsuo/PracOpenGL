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

@interface GLView : UIView
{
    EAGLContext *m_context;
}

- (void)drawView;

@end
