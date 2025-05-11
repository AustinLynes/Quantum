#include <iostream>

#include "../include/QApplication.h"

extern QApplication* CreateApplication();

int main() {
    auto app = CreateApplication();
    return app->Execute();
}