#include "QWindow.h"

class QGLFWWindow : public QWindow
{
public:
    QGLFWWindow(int width, int height, const char* title);
    ~QGLFWWindow();
    
    void on_create() override;
    void run() override;

private:
    class GLFWwindow* window;
};


