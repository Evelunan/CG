//glIncludes.h 包含OpenGL必要的头文件。
#ifndef _GLINCLUDES_H_INCLUDED_ 
#define _GLINCLUDES_H_INCLUDED_ 
#if defined(_USE_GLEW) 1
#include <GL/glew.h> 
#else 
#include <GLAD/glad.h> 
#include <GL/glext.h>
#endif 
#include <GLFW/glfw3.h> 
#define GLFW_EXPOSE_NATIVE_WIN32  
#include <GLFW/glfw3native.h> 
#define GLM_ENABLE_EXPERIMENTAL
//可能用到的OpenGL数学库、图像加载库 
#include <glm/glm.hpp> 
#include <glm/ext.hpp> 
#include <SOIL2/SOIL2.h>  
#endif //_GLINCLUDES_H_INCLUDED_