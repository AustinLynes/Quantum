#include "QWindow.h"

QWindow::QWindow(int width, int height, const char* title)
    : _width(width), _height(height), _title(title)
{
}

QWindow::~QWindow()
{
}