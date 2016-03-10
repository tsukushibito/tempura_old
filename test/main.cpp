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

temp::system::Window::SPtr g_window;

void init()
{
    using namespace temp;
    using namespace temp::system;

	ConsoleLogger::initialize();

	setCurrentDirectory("../");
	ConsoleLogger::trace("Current directory : {}", getCurrentDirectory().getAbsolute());

	auto load_thread = ThreadPool::create("Load", 1);
	auto render_thread = ThreadPool::create("Render", 1);
	auto worker_thread = ThreadPool::create("Worker", 1);

	Test::initialize(load_thread);
	auto res = Test::create("");

    g_window = Window::create();

	graphics::DeviceParameter devParam;
	devParam.load_thread = load_thread;
	devParam.render_thread = render_thread;
	devParam.worker_thread = worker_thread;
	devParam.window = g_window;
	auto device = graphics::Device::create(devParam);
	device->createVertexShaderFromSource(String());
}

void term()
{
    using namespace temp;
    using namespace temp::system;

	g_window = nullptr;

	ConsoleLogger::terminate();
}

void update()
{
}

int main(int argc, char const* argv[])
{
    using namespace temp;
    using namespace temp::system;
    
	Application::getInstance().setInitializeFunction(init);
	Application::getInstance().setUpdateFunction(update);
	Application::getInstance().setTerminateFunction(term);

    Application::getInstance().run();
    
    return 0;
}
