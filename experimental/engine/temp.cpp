#include <iostream>
#define TEMP_EXPORT
#include <temp.h>

extern "C" {
TEMP_DECLSPEC void tempCreateEngine()
{
    std::cout << "tempCreateEngine()" << std::endl;
}

TEMP_DECLSPEC void tempDestroyEngine()
{
    std::cout << "tempDestroyEngine()" << std::endl;
}
}