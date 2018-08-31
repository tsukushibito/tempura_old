#import <Cocoa/Cocoa.h>
#import <QuartzCore/QuartzCore.h>
#include "temp/core/core.h"
#include "temp/system/mac/mac_utility.h"

namespace temp {
namespace system {
namespace mac {

void* GetViewHandle(const void* window_handle, bool set_metal_layer) {
    TEMP_ASSERT(window_handle != nullptr, "window_handle must not be nullptr!");
    NSWindow* ns_window = (__bridge NSWindow*)window_handle;
    NSView* ns_view = [ns_window contentView];
    if(set_metal_layer) {
        if (![ns_view.layer isKindOfClass:[CAMetalLayer class]]) {
            [ns_view setLayer:[CAMetalLayer layer]];
            [ns_view setWantsLayer:YES];
        }
    }
    return ns_view;
}

}
}
}
