/**
 * @file main.cpp
 * @brief test main
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-20
 */

#include <cassert>
#include "temp.h"

class Test : public temp::resource::ResourceBase<Test> {
	// friend class temp::resource::ResourceBase<Test>;
public:
	Test(const temp::system::Path &path) : ResourceBase(path) {}
private:
	virtual void loginImpl(){}
	virtual void logoutImpl(){}
};

int main(int argc, char const* argv[])
{
    using namespace temp;
    using namespace temp::system;
    
	ConsoleLogger::initialize();

	setCurrentDirectory("../");
	ConsoleLogger::trace("Current directory : {}", getCurrentDirectory().getAbsolute());

	auto thread_pool = ThreadPool::create("Load", 1);
	Test::initialize(thread_pool);
	auto res = Test::create("");

    auto window = Window::create();

    Application::getInstance().run();

	ConsoleLogger::terminate();
    
    return 0;
}
