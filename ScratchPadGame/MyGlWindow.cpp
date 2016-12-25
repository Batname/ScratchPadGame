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
    float shipOrientation = 0.0f;
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
    
    int minSize = min(width(), height());
    Vector2D viewPortLoacation;
    viewPortLoacation.x = width() / 2 - minSize / 2;
    viewPortLoacation.y = height() / 2 - minSize / 2;
    glViewport(viewPortLoacation.x, viewPortLoacation.y, minSize, minSize);
    
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
    rotateShip();
    updateVelocity();
    shipPosition += shipVelosity * clock->getDeltaTime();

//    float deltaTime = clock->getDeltaTime();
//    Vector2D velocity(0.05f, 0.05f);
//    shipPosition = shipPosition + velocity * deltaTime;
    repaint();
}

void MyGlWindow::brake(float * velocity, float accelaration)
{
    const float brakeAccelaration = 4.0f;
    if (*velocity < 0.1f && *velocity > -0.1f) {
        *velocity = 0.0f;
    } else if (*velocity < 0) {
        *velocity += accelaration * brakeAccelaration;
    } else if (*velocity > 0) {
        *velocity -= accelaration * brakeAccelaration;
    }
}

void MyGlWindow::rotateShip()
{
    const float ANGULAR_MOVEMENT = 0.1f;
    if (pressedKeys.contains(Qt::Key_Right)) {
        shipOrientation -= ANGULAR_MOVEMENT;
    }
    if (pressedKeys.contains(Qt::Key_Left)) {
       shipOrientation += ANGULAR_MOVEMENT;
    }
}

void MyGlWindow::updateVelocity()
{
//    float accelaration = 0.2f * clock->getDeltaTime();
//    if (pressedKeys.contains(Qt::Key_Up)) {
//        shipVelosity.y += accelaration;
//    }
//    if (pressedKeys.contains(Qt::Key_Down)) {
//        shipVelosity.y -= accelaration;
//    }
//    if (pressedKeys.contains(Qt::Key_Right)) {
//        shipVelosity.x += accelaration;
//    }
//    if (pressedKeys.contains(Qt::Key_Left)) {
//        shipVelosity.x -= accelaration;
//    }
//    if (pressedKeys.contains(Qt::Key::Key_Space)) {
//        brake(&shipVelosity.x, accelaration);
//        brake(&shipVelosity.y  , accelaration);
//    }
}

void MyGlWindow::paintGL()
{

    // clear
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    Vector2D transformedVerts[NUM_VERTS];
    Matrix2D op = Matrix2D::rotate(shipOrientation);
    for (unsigned int i = 0; i < NUM_VERTS; i++) {
        transformedVerts[i] = op * vertices[i];
    }
    
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(transformedVerts), transformedVerts);
    
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
