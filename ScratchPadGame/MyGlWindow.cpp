#include "MyGlWindow.hpp"

using namespace Math;

namespace {
    Vector2D vertices[] = {
        Vector2D(+0.0f, +0.1f), // Left
        Vector2D(-0.1f, -0.1f), // Right
        Vector2D(+0.1f, -0.1f), // Top
    };
    
    const unsigned int NUM_VERTS = sizeof(vertices) / sizeof(*vertices);
    Vector2D shipPosition;
    Vector2D shipVelosity;
}


using namespace std;

MyGlWindow::MyGlWindow()
{
    qTimer = new QTimer(this);
    clock = new Timing::Clock;
    installEventFilter(this);
}


MyGlWindow::~MyGlWindow()
{
    delete qTimer;
    delete program;
    delete clock;
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
    clock->run();
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
    
    connect(qTimer, SIGNAL(timeout()), this, SLOT(myUpdate()));
    qTimer->start(0);
}


void MyGlWindow::myUpdate()
{
    clock->update();
    updateVelocity();
    shipPosition = shipPosition + shipVelosity * clock->getDeltaTime();

//    float deltaTime = clock->getDeltaTime();
//    Vector2D velocity(0.05f, 0.05f);
//    shipPosition = shipPosition + velocity * deltaTime;
    repaint();
}

void MyGlWindow::updateVelocity()
{
    float accelaration = 0.2f * clock->getDeltaTime();
    if (pressedKeys.contains(Qt::Key_Up)) {
        shipVelosity.y += accelaration;
    }
    if (pressedKeys.contains(Qt::Key_Down)) {
        shipVelosity.y -= accelaration;
    }
    if (pressedKeys.contains(Qt::Key_Right)) {
        shipVelosity.x += accelaration;
    }
    if (pressedKeys.contains(Qt::Key_Left)) {
        shipVelosity.x -= accelaration;
    }
}

void MyGlWindow::paintGL()
{
    // glViewport(0, 0, width(), height());

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

bool MyGlWindow::eventFilter(QObject * obj, QEvent * event)
{
    if (event->type() == QEvent::KeyPress) {
        pressedKeys += ((QKeyEvent*)event)->key();
    } else if (event->type() == QEvent::KeyRelease) {
        pressedKeys -= ((QKeyEvent*)event)->key();
    }
    return false;
}


// aoutogenerated
#include "MyGlWindow_moc.h"
// /usr/local/Cellar/qt@5.5/5.5.1/bin/moc ~/Project/openGL/ScratchPadGame/ScratchPadGame/MyGlWindow.hpp
