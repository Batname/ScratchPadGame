
#include "FileLoader.hpp"

FileLoader::FileLoader(const char * filePath)
{
    file = new QFile(filePath);
    
    assert(file->open(QIODevice::ReadOnly | QIODevice::Text));
}

QString FileLoader::getString()
{
    QByteArray total;
    QByteArray line;
    while (!file->atEnd()) {
        line = file->read(1024);
        total.append(line);
    }
        
    return QString(total);

}

FileLoader::~FileLoader()
{
    file->close();
    delete file;
}
