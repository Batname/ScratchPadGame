#include "MyGlWindow.hpp"

// Shaders
const GLchar* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f, // Left
    0.5f, -0.5f, 0.0f, // Right
    0.0f,  0.5f, 0.0f  // Top
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

void MyGlWindow::initializeShader()
{
    program = new QGLShaderProgram();
    program->addShaderFromSourceCode(QGLShader::Vertex, vertexShaderSource);
    program->addShaderFromSourceCode(QGLShader::Fragment,fragmentShaderSource);
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
