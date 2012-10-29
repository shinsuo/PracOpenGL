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
        
        m_renderingEngine = CreateRender1();
        [m_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:eaglLayer];
        
        m_renderingEngine->Initialize(CGRectGetWidth(frame), CGRectGetHeight(frame));
        [self drawView:nil];
        
        
        m_timestamp = CACurrentMediaTime();
        
        CADisplayLink *displayLink;
        displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(drawView:)];
        NSLog(@"m_timestamp:%f--",m_timestamp);
        
        [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        
        [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
        
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(didRotate:)
                                                     name:UIDeviceOrientationDidChangeNotification
                                                   object:nil];
        
        /*
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
         */
        
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

- (void)drawView:(CADisplayLink *)displayLink
{
    NSLog(@"drawView;%@",displayLink);
    
    if (displayLink != nil) {
        float elapsedSeconds = displayLink.timestamp - m_timestamp;
        m_timestamp = displayLink.timestamp;
        m_renderingEngine->UpdateAniamtion(elapsedSeconds);
    }
    
    m_renderingEngine->Render();
    [m_context presentRenderbuffer:GL_RENDERBUFFER];
/*
    glClearColor(0.5f, 0.5f, 0.5f, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    [m_context presentRenderbuffer:GL_RENDERBUFFER_OES];
*/
    
/*
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
  */  
}

- (void)didRotate:(NSNotification *)notification
{
    UIDeviceOrientation orientation = [[UIDevice currentDevice] orientation];
    m_renderingEngine->OnRotate((DeviceOrientation)orientation);
    [self drawView:nil];
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
