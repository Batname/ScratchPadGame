#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp

#include "includes.h"

#include "FileLoader.hpp"

class ShaderProgram : public QGLShaderProgram
{
public:
    ShaderProgram(const char * vertexShaderPath, const char * fragmentShaderPath);
protected:
private:

};

#endif /* ShaderProgram_hpp */
