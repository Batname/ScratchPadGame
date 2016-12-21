#ifndef MyGlWindow_hpp
#define MyGlWindow_hpp

#include <BatGameEngine/BatGameEngine.hpp>
#include <cassert>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <QtOpenGL/qgl.h>

class MyGlWindow : public QGLWidget
{
public:
protected:
    void initializeGL();
    void paintGL();
private:
    GLuint VBO, VAO;
    GLuint shaderProgram;

    void sendDataToOpenGL();
    void initializeShader();

};

#endif /* MyGlWindow_hpp */
