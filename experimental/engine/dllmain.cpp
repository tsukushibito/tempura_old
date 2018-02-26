#include "temp/common/define.h"
#ifdef TEMP_PLATFORM_WINDOWS
#include <Windows.h>
BOOL WINAPI DllMain(HINSTANCE hinstDLL,  // DLL モジュールのハンドル
                    DWORD fdwReason,     // 関数を呼び出す理由
                    LPVOID lpvReserved   // 予約済み
) {
  switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
      break;
    case DLL_THREAD_ATTACH:
      break;
    case DLL_THREAD_DETACH:
      break;
    case DLL_PROCESS_DETACH:
      break;
  }
  return TRUE;
}
#endif