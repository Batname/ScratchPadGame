#ifndef MyGlWindow_hpp
#define MyGlWindow_hpp

#include <BatGameEngine/BatGameEngine.hpp>
#include <cassert>
#include <thread>
#include <functional>

#include <QtOpenGL/qgl.h>
#include <QtCore/qfile.h>
#include <QtCore/qtimer.h>

#include "ShaderProgram.hpp"
#include "Timer.hpp"

class MyGlWindow : public QGLWidget
{
public:
    MyGlWindow();
    ~MyGlWindow();
    
protected:
    void initializeGL();
    void paintGL();
private:
    GLuint VBO, VAO;
    GLuint shaderProgram;
    Timer * timer;
    
    ShaderProgram * program;

    void sendDataToOpenGL();
    QByteArray getTotal(QFile * file);
    
    void myUpdate();

};

#endif /* MyGlWindow_hpp */
