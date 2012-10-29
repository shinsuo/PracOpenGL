//
//  IRenderingEngine1.cpp
//  HelloArrow
//
//  Created by shin on 12-10-29.
//  Copyright (c) 2012年 Indie Developer. All rights reserved.
//

#include "IRenderingEngine.h"

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#include <iostream>
#include <cmath>

#define STRINGIFY(A) #A
#include "shader/Simple.vert"
#include "shader/Simple.frag"

static const float RevolutionPerSecond = 1;

class RenderingEngine2:public IRenderingEngine
{
    GLuint  m_frameBuffer;
    GLuint  m_renderBuffer;
    float   m_currenAngle;
    float   m_desiredAngle;
    float   RotationDirection() const;
    
    //*OpenGL ES 2.0 Version
    GLuint  m_simpleProgram;
    GLuint  BuildShader(const char *source,GLenum shaderType) const;
    GLuint  BuildProgram(const char *vShader,const char *fShader) const;
    void    ApplyOrtho(float maxX,float maxY) const;
    void    ApplyRotation(float degrees) const;
    //*/
    
public:
    RenderingEngine2();
    void Initialize(int width,int height);
    void Render() const;
    void UpdateAniamtion(float timeStep);
    void OnRotate(DeviceOrientation newOrientation);
};

IRenderingEngine* CreateRender2()
{
    return new RenderingEngine2();
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

#pragma mark Public Method

RenderingEngine2::RenderingEngine2()
{
    /*OpenGL ES 1.0 Version
    glGenRenderbuffersOES(1, &m_renderBuffer);
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, m_renderBuffer);
     //*/
    
    //*OpenGL ES 2.0 Version
    glGenRenderbuffers(1, &m_renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_renderBuffer);

}

void RenderingEngine2::Initialize(int width, int height)
{
    /*OpenGL ES 1.0 Version
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
    //*/
    
    //*OpenGL ES 2.0 Version
    glGenFramebuffers(1, &m_frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                              GL_COLOR_ATTACHMENT0,
                              GL_RENDERBUFFER,
                              m_renderBuffer);
    glViewport(0, 0, width, height);
    m_simpleProgram = BuildProgram(SimpleVertexShader, SimpleFragmentShader);
    glUseProgram(m_simpleProgram);
    
    ApplyOrtho(2, 3);
    //*/
    
    
    OnRotate(DeviceOrientationPortrait);
    m_currenAngle = m_desiredAngle;
}

void RenderingEngine2::Render() const
{
    glClearColor(0.5, 0.5, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    //*OpenGL ES 2.0 Version
    ApplyRotation(m_currenAngle);
    GLuint positionSlot = glGetAttribLocation(m_simpleProgram, "Position");
    GLuint colorSlot = glGetAttribLocation(m_simpleProgram, "SourceColor");
    
    glEnableVertexAttribArray(positionSlot);
    glEnableVertexAttribArray(colorSlot);
    
    GLsizei stride = sizeof(Vertex);
    const GLvoid *pCoords = &Vertices[0].Position[0];
    const GLvoid *pColors = &Vertices[0].Color[0];
    
    glVertexAttribPointer(positionSlot, 2, GL_FLOAT, GL_FALSE, stride, pCoords);
    glVertexAttribPointer(colorSlot, 4, GL_FLOAT, GL_FALSE, stride, pColors);
    
    GLsizei vertexCount = sizeof(Vertices)/sizeof(Vertex);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    
    glDisableVertexAttribArray(positionSlot);
    glDisableVertexAttribArray(colorSlot);
    
    //*/
    
    /*OpenGL ES 1.0 Version
    glPushMatrix();
    glRotatef(m_currenAngle, 0, 0, 1);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    
    glVertexPointer(2, GL_FLOAT, sizeof(Vertex), &Vertices[0].Position[0]);
    glColorPointer(4, GL_FLOAT, sizeof(Vertex), &Vertices[0].Color[0]);
    
    GLsizei vertexCount = sizeof(Vertices)/sizeof(Vertex);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    
    glPopMatrix();
    // */
}

void RenderingEngine2::UpdateAniamtion(float timeStep)
{
    float direction = RotationDirection();
    if (direction == 0) {
        return;
    }
    
    float degrees = timeStep*360*RevolutionPerSecond;
    m_currenAngle += degrees*direction;
    
    if (m_currenAngle >= 360) {
        m_currenAngle -= 360;
    }else if (m_currenAngle < 0){
        m_currenAngle += 360;
    }
    
    if (RotationDirection() != direction) {
        m_currenAngle = m_desiredAngle;
    }
}

void RenderingEngine2::OnRotate(DeviceOrientation newOrientation)
{
    float angle = 0;
    switch (newOrientation) {
        case DeviceOrientationLandscapeLeft:
            angle = 270;
            break;
        case DeviceOrientationPortraitUpsideDown:
            angle = 180;
            break;
        case DeviceOrientationLandscapeRight:
            angle = 90;
            break;
        default:
            break;
    }
    
    m_desiredAngle = angle;
}

#pragma mark Private Method
float RenderingEngine2::RotationDirection()const
{
    float delta = m_desiredAngle - m_currenAngle;
    if (delta == 0) {
        return 0;
    }
    bool counterclockwise = ((delta > 0 && delta <= 180)||(delta < -180));
    return counterclockwise ? +1:-1;
}

GLuint RenderingEngine2::BuildProgram(const char *vShader,const char *fShader) const
{
    GLuint vertexShader     = BuildShader(vShader, GL_VERTEX_SHADER);
    GLuint fragmentShader   = BuildShader(fShader, GL_FRAGMENT_SHADER);
    
    GLuint programHandle    = glCreateProgram();
    glAttachShader(programHandle, vertexShader);
    glAttachShader(programHandle, fragmentShader);
    glLinkProgram(programHandle);
    
    GLint linkSuccess;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &linkSuccess);
    if (linkSuccess == GL_FALSE) {
        GLchar message[256];
        glGetProgramInfoLog(programHandle, sizeof(message), 0, &message[0]);
        std::cout << message;
        exit(1);
    }
    return programHandle;
}

GLuint RenderingEngine2::BuildShader(const char *source,GLenum shaderType) const
{
    GLuint shaderHandle = glCreateShader(shaderType);
    glShaderSource(shaderHandle, 1, &source, 0);
    glCompileShader(shaderHandle);
    
    GLint compileSuccess;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileSuccess);
    
    if (compileSuccess == GL_FALSE) {
        GLchar message[256];
        glGetShaderInfoLog(shaderHandle, sizeof(message), 0, &message[0]);
        std::cout << message;
        exit(1);
    }
    return shaderHandle;
}

void RenderingEngine2::ApplyOrtho(float maxX, float maxY) const
{
    float a = 1.0f/maxX;
    float b = 1.0f/maxY;
    
    float ortho[16] = {
        a,0,0,0,
        0,b,0,0,
        0,0,-1,0,
        0,0,0,1
    };
    
    GLint projectionUniform = glGetUniformLocation(m_simpleProgram, "Projection");
    glUniformMatrix4fv(projectionUniform, 1, 0, &ortho[0]);
}

void RenderingEngine2::ApplyRotation(float degrees) const
{
    float radians = degrees * 3.14158f /180.0f;
    float s = std::sin(radians);
    float c = std::cos(radians);
    
    float zRotation[16] = {
        c,s,0,0,
        -s,c,0,0,
        0,0,1,0,
        0,0,0,1
    };
    
    GLint modelviewUniform = glGetUniformLocation(m_simpleProgram, "Modelview");
    glUniformMatrix4fv(modelviewUniform, 1, 0, &zRotation[0]);
}






