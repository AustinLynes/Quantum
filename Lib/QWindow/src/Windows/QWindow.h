#pragma once

class QWindow 
{
public:
    QWindow(int width, int height, const char* title);
    virtual ~QWindow();
    
    virtual void on_create() = 0;
    virtual void run() = 0;

    protected:
        int _width;
        int _height;
        const char* _title;
};
