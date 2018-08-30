#import <Cocoa/Cocoa.h>
#include "temp/system/mac/mac_utility.h"

namespace temp {
namespace system {
namespace mac {

void* GetViewHandle(void* window_handle) {
    NSWindow* ns_window = (__bridge NSWindow*)window_handle;
    NSView* ns_view = [ns_window contentView];
    return ns_view;
}

}
}
}