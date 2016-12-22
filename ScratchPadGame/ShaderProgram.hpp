#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp

#include <QtOpenGL/qglshaderprogram.h>

#include "FileLoader.hpp"

class ShaderProgram : public QGLShaderProgram
{
public:
    ShaderProgram(char * vertexShaderPath, char * fragmentShaderPath);
protected:
private:

};

#endif /* ShaderProgram_hpp */
