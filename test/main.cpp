/**
 * @file main.cpp
 * @brief test main
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-20
 */

#include "temp.h"

class Test : public temp::resource::ResourceBase<Test> {
public:
	Test(const temp::system::Path &path) : ResourceBase(path) {}
};
using TestResource = temp::resource::ResourceBase<Test>;

int main(int argc, char const* argv[])
{
    using namespace temp;
    using namespace temp::system;
    
	ConsoleLogger::initialize();

	setCurrentDirectory("../");
	ConsoleLogger::trace("Current directory : {}", getCurrentDirectory().getAbsolute());

	auto thread_pool = ThreadPool::create("Load", 1);
	TestResource::initialize(thread_pool);
	auto res = TestResource::create("");

    auto window = Window::create();

    Application::getInstance().run();

	ConsoleLogger::terminate();
    
    return 0;
}
