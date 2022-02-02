#pragma once
#include <glad/glad.h>
#include <iostream>

GLuint PrintError_(GLuint errorType, const char* errorContent, const char* file, int line);
GLenum glCheckError_(const char* file, int line);

#ifndef COMMONTOOL
#define COMMONTOOL

#define ET_READFILE 0x001
#define ET_SHADERPROGRAM 0x002
#define ET_SHADER 0x003
#define ET_FRAMEBUFFER 0x004

#define PrintError(errorType,errorContent) PrintError_(errorType,errorContent,__FILE__,__LINE__)
#define glCheckError() glCheckError_(__FILE__, __LINE__) 
#endif
