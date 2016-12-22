#include "ShaderProgram.hpp"

#include <iostream>

ShaderProgram::ShaderProgram(char * vertexShaderPath, char * fragmentShaderPath)
{
    FileLoader vertexShaderFile(vertexShaderPath);
    FileLoader fragmentShaderFile(fragmentShaderPath);
        
    this->addShaderFromSourceCode(QGLShader::Vertex, vertexShaderFile.getString());
    this->addShaderFromSourceCode(QGLShader::Fragment, fragmentShaderFile.getString());
    
    this->link();
    this->bind();
}
