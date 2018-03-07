#include "temp/common/define.h"
#ifdef TEMP_PLATFORM_WINDOWS
#include <Windows.h>
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
namespace {

struct Debug {
  Debug() {
    // _CrtSetBreakAlloc(1999);
  }
};

Debug debug;

}

BOOL WINAPI DllMain(HINSTANCE hinstDLL,  // DLL モジュールのハンドル
                    DWORD fdwReason,     // 関数を呼び出す理由
                    LPVOID lpvReserved   // 予約済み
) {
  (void*)lpvReserved;
  (void*)hinstDLL;

  switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
      break;
    case DLL_THREAD_ATTACH:
      break;
    case DLL_THREAD_DETACH:
      break;
    case DLL_PROCESS_DETACH:
		_CrtDumpMemoryLeaks();
      break;
  }
  return TRUE;
}
#endif