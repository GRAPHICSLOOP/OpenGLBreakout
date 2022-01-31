#include "CommonTool.h"

GLuint PrintError_(GLuint errorType, const char* errorContent, const char* file, int line)
{
    GLuint errorCode = errorType;

    switch (errorType)
    {
    case ET_READFILE:
        std::cout << "ERROR::READFILE::" << errorContent << std::endl;
        std::cout << "file: " << file << " line: " << line << std::endl;
        break;
    case ET_SHADERPROGRAM:
        std::cout << "ERROR::SHADERPROGRAM::" << errorContent << std::endl;
        std::cout << "file: " << file << " line: " << line << std::endl;
        break;
    case ET_SHADER:
        std::cout << "ERROR::SHADER::" << errorContent << std::endl;
        std::cout << "file: " << file << " line: " << line << std::endl;
        break;
    default:
        break;
    }

    return errorCode;
}