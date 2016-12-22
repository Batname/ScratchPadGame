#ifndef MyGlWindow_hpp
#define MyGlWindow_hpp

#include "includes.h"

#include "ShaderProgram.hpp"

class MyGlWindow : public QGLWidget
{
    Q_OBJECT
public:
    MyGlWindow();
    ~MyGlWindow();
    
protected:
    void initializeGL();
    void paintGL();
private:
    GLuint VBO, VAO;
    GLuint shaderProgram;
    QTimer * qTimer;
    Timing::Clock * clock;
    
    ShaderProgram * program;

    void sendDataToOpenGL();
    QByteArray getTotal(QFile * file);
    
public slots:
    void myUpdate();

};

#endif /* MyGlWindow_hpp */
