#include "includes.h"

#include "MyGlWindow.hpp"

int main(int argc, char **argv) {
    
    QApplication app(argc, argv);
    
    /* ---- init openGL ---- */
    QGLFormat glFormat;
    glFormat.setVersion(3, 2);
    glFormat.setProfile(QGLFormat::CoreProfile);
    
    // Set the default GL format to OpenGL 3.2 Core
    QGLFormat::setDefaultFormat(glFormat);

    MyGlWindow window;
    window.show();
    
    return app.exec();
}
