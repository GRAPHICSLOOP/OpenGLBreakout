﻿#pragma once
#include <glad/glad.h>
#include <iostream>

GLuint PrintError_(GLuint errorType, const char* errorContent, const char* file, int line);

#ifndef COMMONTOOL
#define COMMONTOOL

#define ET_READFILE 0x001

#define PrintError(errorType,errorContent) PrintError_(errorType,errorContent,__FILE__,__LINE__)

#endif