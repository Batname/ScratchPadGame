#include "MyGlWindow.hpp"

using namespace Math;

namespace {
    Vector2D vertices[] = {
        Vector2D(+0.0f, +0.1f), // Left
        Vector2D(-0.1f, -0.1f), // Right
        Vector2D(+0.1f, -0.1f), // Top
    };
    
    const unsigned int NUM_VERTS = sizeof(vertices) / sizeof(*vertices);
    Vector2D shipPosition(0.5f, 0.5f);
}


using namespace std;

MyGlWindow::MyGlWindow()
{
    timer = new Timer();
}

MyGlWindow::~MyGlWindow()
{
    delete timer;
    delete program;
}

void MyGlWindow::initializeGL()
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cout << "Failed to inin glew with experemental"  << endl;
    }
    
    // openGl options
    glEnable(GL_DEPTH_TEST);
    
    program = new ShaderProgram("resources/shaders/vertexShader.glsl", "resources/shaders/fragmentShader.glsl");
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

void MyGlWindow::sendDataToOpenGL()
{
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), nullptr, GL_DYNAMIC_DRAW);
    
    
    GLint positionAttrib = program->attributeLocation("position");
    glVertexAttribPointer(positionAttrib, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(positionAttrib);
    
    // delay::nanoseconds
    timer->create(0, 1, std::bind(&MyGlWindow::myUpdate, this));
}
int debugCount = 0;

void MyGlWindow::myUpdate()
{
    std::cout << "frame" << debugCount++ << std::endl;
}

void MyGlWindow::paintGL()
{
    // clear
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    Vector2D translatedVerts[NUM_VERTS];
    
    for (unsigned int i = 0; i < NUM_VERTS; i++) {
        translatedVerts[i] = vertices[i] + shipPosition;
    }
    
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(translatedVerts), translatedVerts);
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
