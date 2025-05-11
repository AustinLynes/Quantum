#pragma once

class QWindowFactory  {
public:
    static void* CreateWindowGLFW(int width, int height, const char* title);
    static void DestroyWindowGLFW(void* window);
    static void RunWindowGLFW(void* window);

};