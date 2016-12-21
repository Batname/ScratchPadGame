#include "MyGlWindow.hpp"

static GLfloat vertices[] = {
    +0.0f, +0.1f, 0.0f, // Left
    -0.1f, -0.1f, 0.0f, // Right
    +0.1f, -0.1f, 0.0f  // Top
};

using namespace std;

void MyGlWindow::initializeGL()
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cout << "Failed to inin glew with experemental"  << endl;
    }
    
    // openGl options
    glEnable(GL_DEPTH_TEST);
    
    initializeShader();
    sendDataToOpenGL();
}

QByteArray MyGlWindow::getTotal(QFile * file)
{
    QByteArray total;
    QByteArray line;
    while (!file->atEnd()) {
        line = file->read(1024);
        total.append(line);
    }
    
    return total;
}

void MyGlWindow::initializeShader()
{
    QFile vertexShaderFile("resources/shaders/vertexShader.glsl");
    QFile fragmentShaderFile("resources/shaders/fragmentShader.glsl");

    assert(vertexShaderFile.open(QIODevice::ReadOnly | QIODevice::Text));
    assert(fragmentShaderFile.open(QIODevice::ReadOnly | QIODevice::Text));

    QString vertexShaderCode(getTotal(&vertexShaderFile));
    QString fragmentShaderCode(getTotal(&fragmentShaderFile));

    vertexShaderFile.close();
    fragmentShaderFile.close();
    
    program = new QGLShaderProgram();
    program->addShaderFromSourceCode(QGLShader::Vertex, vertexShaderCode);
    program->addShaderFromSourceCode(QGLShader::Fragment,fragmentShaderCode);
    program->link();
    program->bind();
}

void MyGlWindow::sendDataToOpenGL()
{
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    
    GLint positionAttrib = program->attributeLocation("position");
    glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(positionAttrib);

}

void MyGlWindow::paintGL()
{
    // clear
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
