#include "CommonTool.h"

GLuint PrintError_(GLuint errorType, const char* errorContent, const char* file, int line)
{
    GLuint errorCode = errorType;
    std::string err = "";
    switch (errorType)
    {
    case ET_READFILE:
        err = "ERROR::READFILE::";
        break;
    case ET_SHADERPROGRAM:
        err = "ERROR::SHADERPROGRAM::";
        break;
    case ET_SHADER:
        err = "ERROR::SHADER::";
        break;
    case ET_FRAMEBUFFER:
        err = "ERROR::FRAMEBUFFER::";
        break;
    case ET_FREETYPE:
        err = "ERROR::FREETYPE::";
    default:
        break;
    }
    std::cout << err << errorContent << std::endl;
    std::cout << "file: " << file << " line: " << line << std::endl;
    return errorCode;
}

GLenum glCheckError_(const char* file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
        case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
        case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
        case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
        case 0x0503:                error = "STACK_OVERFLOW"; break;
        case 0x0504:               error = "STACK_UNDERFLOW"; break;
        case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
        case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}
