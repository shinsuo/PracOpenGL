//
//  IRenderingEngine1.cpp
//  HelloArrow
//
//  Created by shin on 12-10-29.
//  Copyright (c) 2012年 Indie Developer. All rights reserved.
//

#include "IRenderingEngine.h"

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>

class RenderingEngine1:public IRenderingEngine
{
    GLuint m_frameBuffer;
    GLuint m_renderBuffer;
            
public:
    RenderingEngine1();
    void Initialize(int width,int height);
    void Render() const;
    void UpdateAniamtion(float timeStep);
    void OnRotate(DeviceOrientation newOrientation);
};

IRenderingEngine* CreateRender1()
{
    return new RenderingEngine1();
}

typedef struct {
    float Position[2];
    float Color[4];
}Vertex;

const Vertex Vertices[] = {
    {{-0.5,-0.866},{1,1,0.5f,1}},
    {{0.5,-0.866},{1,1,0.5f,1}},
    {{0,1},{1,1,0.5f,1}},
    {{-0.5,-0.866},{0.5f,0.5f,0.5f,1}},
    {{0.5,-0.866},{0.5f,0.5f,0.5f,1}},
    {{0,-0.4f},{0.5f,0.5f,0.5f,1}},
};

RenderingEngine1::RenderingEngine1()
{
    glGenRenderbuffersOES(1, &m_renderBuffer);
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, m_renderBuffer);
}

void RenderingEngine1::Initialize(int width, int height)
{
    glGenFramebuffersOES(1, &m_frameBuffer);
    glBindFramebufferOES(GL_FRAMEBUFFER_OES, m_frameBuffer);

    glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES,
                                 GL_COLOR_ATTACHMENT0_OES,
                                 GL_RENDERBUFFER_OES,
                                 m_renderBuffer);
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    
    const float maxX = 2;
    const float maxY = 3;
    glOrthof(-maxX, +maxX, -maxY, +maxY, -1, 1);
    
    glMatrixMode(GL_MODELVIEW);
}

void RenderingEngine1::Render() const
{
    glClearColor(0.5, 0.5, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    glVertexPointer(2, GL_FLOAT, sizeof(Vertex), &Vertices[0].Position[0]);
    glColorPointer(4, GL_FLOAT, sizeof(Vertex), &Vertices[0].Color[0]);
    
    GLsizei vertexCount = sizeof(Vertices)/sizeof(Vertex);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}












