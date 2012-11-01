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

typedef struct {
    GLfloat x;
    GLfloat y;
    GLfloat z;
}Vertex3D;

typedef struct {
    Vertex3D v1;
    Vertex3D v2;
    Vertex3D v3;
}Triangle3D;

static inline Vertex3D Vertex3DMake(GLfloat x,GLfloat y,GLfloat z)
{
    Vertex3D v3D;
    v3D.x = x; v3D.y = y; v3D.z = z;
    return v3D;
}

static inline Triangle3D Triangle3DMake(Vertex3D v1,Vertex3D v2,Vertex3D v3)
{
    Triangle3D t3D;
    t3D.v1 = v1; t3D.v2 = v2; t3D.v3 = v3;
    return t3D;
}

static inline void Vertex3DSet(Vertex3D *vertex,CGFloat inX,CGFloat inY,CGFloat inZ)
{
    vertex->x = inX;    vertex->y = inY;    vertex->z = inZ;
}


@interface GLView : UIView
{
    EAGLContext *m_context;
}

- (void)drawView;

@end
