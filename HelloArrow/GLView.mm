//
//  GLView.m
//  HelloArrow
//
//  Created by shin on 12-10-28.
//  Copyright (c) 2012年 Indie Developer. All rights reserved.
//

#import "GLView.h"

@implementation GLView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        
        CAEAGLLayer *eaglLayer = (CAEAGLLayer *)super.layer;
        eaglLayer.opaque = YES;
        
        m_context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
        
        if (!m_context || ![EAGLContext setCurrentContext:m_context]) {
            [self release];
            return nil;
        }
        
        GLuint frameBuffer,renderBuffer;
        glGenFramebuffers(1, &frameBuffer);
        glGenRenderbuffers(1, &renderBuffer);
        
        glBindFramebufferOES(GL_FRAMEBUFFER_OES, frameBuffer);
        glBindRenderbufferOES(GL_RENDERBUFFER_OES, renderBuffer);
        
        [m_context renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:eaglLayer];
        
        glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES,
                                     GL_RENDERBUFFER_OES, renderBuffer);
        
        glViewport(0, 0, CGRectGetWidth(frame), CGRectGetHeight(frame));
        
        [self drawView];
        
    }
    return self;
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

- (void)setOpenGL
{
    
}

- (void)drawView
{
    glClearColor(0.5f, 0.5f, 0.5f, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    [m_context presentRenderbuffer:GL_RENDERBUFFER_OES];
}

- (void)dealloc
{
    if ([EAGLContext currentContext] == m_context) {
        [EAGLContext setCurrentContext:nil];
    }
    
    [m_context release];
    [super dealloc];
}

@end
