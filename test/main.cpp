/**
 * @file main.cpp
 * @brief test main
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-20
 */

#include "temp.h"
#include "temp/system/application.h"
#include "temp/system/window.h"

int main(int argc, char const* argv[])
{
    using namespace temp;
    using namespace temp::system;
    
    auto window = Window::create();
    Application::getInstance().run();
    
    return 0;
}
