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
//    glClearColor(0.5f, 0.5f, 0.5f, 1);
//    glClear(GL_COLOR_BUFFER_BIT);
    
    Vertex3D vertex1 = Vertex3DMake (0.0, 1.0, -3.0);
    Vertex3D vertex2 = Vertex3DMake (1.0, 0.0, -3.0);
    Vertex3D vertex3 = Vertex3DMake (-1.0, 0.0, -3.0);
    Triangle3D triangle = Triangle3DMake (vertex1, vertex2, vertex3);
    
    glLoadIdentity ();
    glClearColor (0.7, 0.7, 0.7, 1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glEnableClientState (GL_VERTEX_ARRAY );
    glColor4f(1.0,0.0, 0.0, 1.0);
    glVertexPointer (3, GL_FLOAT , 0, &triangle );
    glDrawArrays (GL_TRIANGLES , 0, 9);
    glDisableClientState (GL_VERTEX_ARRAY );
    
    
//    Triangle3D triangle [2];
//    triangle [0].v1 = Vertex3DMake (0.0, 1.0, -3.0);
//    triangle [0].v2 = Vertex3DMake (1.0, 0.0, -3.0);
//    triangle [0].v3 = Vertex3DMake (-1.0, 0.0, -3.0);
//    triangle [1].v1 = Vertex3DMake (-1.0, 0.0, -3.0);
//    triangle [1].v2 = Vertex3DMake (1.0, 0.0, -3.0);
//    triangle [1].v3 = Vertex3DMake (0.0, -1.0, -3.0);
//    
//    glLoadIdentity ();
//    glClearColor (0.7, 0.7, 0.7, 1.0);
//    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//    glEnableClientState (GL_VERTEX_ARRAY );
//    glColor4f (1.0, 0.0, 0.0, 1.0);
//    glVertexPointer (3, GL_FLOAT, 0, &triangle);
//    glDrawArrays (GL_TRIANGLES , 0, 18);
//    glDisableClientState (GL_VERTEX_ARRAY );
    
    
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
