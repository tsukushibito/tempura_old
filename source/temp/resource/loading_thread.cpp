/**
 * @file loading_thread.cpp
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-04-19
 */

#include "temp/resource/loading_thread.h"

namespace temp {
namespace resource {
temp::system::ThreadPool::SPtr LoadingThread::s_thread_pool;
}
}
