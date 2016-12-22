#ifndef FileLoader_hpp
#define FileLoader_hpp

#include <QtCore/qfile.h>
#include <cassert>

class FileLoader
{
public:
    explicit FileLoader(char * filePath);
    ~FileLoader();
    
    QString getString();
protected:
private:
    QFile * file;
};

#endif /* FileLoader_hpp */
