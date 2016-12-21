#ifndef MyGlWindow_hpp
#define MyGlWindow_hpp

#include <BatGameEngine/BatGameEngine.hpp>
#include <cassert>

#include <QtOpenGL/qgl.h>
#include <QtOpenGL/qglshaderprogram.h>

class MyGlWindow : public QGLWidget
{
public:
    
protected:
    void initializeGL();
    void paintGL();
private:
    GLuint VBO, VAO;
    GLuint shaderProgram;
    
    QGLShaderProgram * program;

    void sendDataToOpenGL();
    void initializeShader();

};

#endif /* MyGlWindow_hpp */
