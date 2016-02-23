/**
 * @file main.cpp
 * @brief test main
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-20
 */

#include "temp.h"

int main(int argc, char const* argv[])
{
    using namespace temp;
    using namespace temp::system;
    
	ConsoleLogger::initialize();

	setCurrentDirectory("../");
	ConsoleLogger::trace("Current directory : {}", getCurrentDirectory().getAbsolute());

    auto window = Window::create();

    Application::getInstance().run();

	ConsoleLogger::terminate();
    
    return 0;
}
