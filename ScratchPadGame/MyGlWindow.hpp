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
    bool eventFilter(QObject * obj, QEvent * event);
private:
    GLuint VBO, VAO;
    GLuint shaderProgram;
    QTimer * qTimer;
    Timing::Clock * clock;
    
    ShaderProgram * program;
    
    QSet<int> pressedKeys;

    void sendDataToOpenGL();
    QByteArray getTotal(QFile * file);
    
    void updateVelocity();
    void rotateShip();
    void brake(float * velocity, float accelaration);
    
public slots:
    void myUpdate();
    void checkKeyState();

};

#endif /* MyGlWindow_hpp */
