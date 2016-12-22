#ifndef MyGlWindow_hpp
#define MyGlWindow_hpp

#include <BatGameEngine/BatGameEngine.hpp>
#include <cassert>

#include <QtOpenGL/qgl.h>
#include <QtCore/qfile.h>

#include "ShaderProgram.hpp"

class MyGlWindow : public QGLWidget
{
public:
    
protected:
    void initializeGL();
    void paintGL();
private:
    GLuint VBO, VAO;
    GLuint shaderProgram;
    
    ShaderProgram * program;

    void sendDataToOpenGL();
    QByteArray getTotal(QFile * file);

};

#endif /* MyGlWindow_hpp */
