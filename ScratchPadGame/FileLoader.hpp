#ifndef FileLoader_hpp
#define FileLoader_hpp

#include "includes.h"

class FileLoader
{
public:
    explicit FileLoader(const char * filePath);
    ~FileLoader();
    
    QString getString();
protected:
private:
    QFile * file;
};

#endif /* FileLoader_hpp */
