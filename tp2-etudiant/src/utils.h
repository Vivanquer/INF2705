#ifndef UTILS_H
#define UTILS_H

#include <string>

#define CHECK_GL_ERROR checkGLError(__FILE__, __LINE__)
void checkGLError(const char* file, int line);

std::string readFile(const char* path);

double rand01();


#endif // UTILS_H
