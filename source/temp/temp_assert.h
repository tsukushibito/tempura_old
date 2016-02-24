/**
 * @file assert.h
 * @brief assert
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-24
 */
#pragma once
#ifndef GUARD_8b79d00eeb164860884f8bdb6ffa34fd
#define GUARD_8b79d00eeb164860884f8bdb6ffa34fd

#include <iostream>

#include "temp/define.h"
#include "temp/type.h"
#include "temp/container.h"

#ifdef TEMP_PLATFORM_WINDOWS
#include <Windows.h>
#endif

namespace temp {
   inline void reportAssertion(const Char *msg, const Char *file, Size line) {
#ifdef TEMP_PLATFORM_WINDOWS
        StringStream log;
        log << file << " : line[" << line << "] : " << msg << std::endl;
        OutputDebugStringA(log.str().c_str());
        DebugBreak();
#else
       std::cout << file << " : line[" << line << "] : " << msg << std::endl;
       __builtin_trap();
#endif
   } 
} // namespace temp

#define TEMP_ASSERT(expr) (void)( (!!(expr)) || (temp::reportAssertion(#expr, __FILE__, __LINE__), 0) )

#endif // GUARD_8b79d00eeb164860884f8bdb6ffa34fd
