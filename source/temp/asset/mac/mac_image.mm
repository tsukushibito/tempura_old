#import <Cocoa/Cocoa.h>
#include "temp/asset/mac/mac_image.h"

namespace temp {
namespace asset {
namespace mac {

ImageData getImageData(NSImage* ns_image) {
    NSBitmapImageRep* image_rep = [NSBitmapImageRep imageRepWithData:[ns_image TIFFRepresentation]];
    ImageData data;
    data.width           = [image_rep pixelsWide];
    data.height          = [image_rep pixelsHigh];
    data.bytes_per_pixel = [image_rep samplesPerPixel];
    data.bitmap_data     = [image_rep bitmapData];
    return data;
}

MacImage::MacImage(const filesystem::path& path) {
    auto file_name = [NSString stringWithUTF8String:path.string().c_str()];
    ns_image_ = [[NSImage alloc] initWithContentsOfFile:file_name];
    image_data_ = getImageData((NSImage*)ns_image_);
}

MacImage::MacImage(const void* data, Size size) {
    auto ns_data = [NSData dataWithBytes:data length:size];
    ns_image_ = [[NSImage alloc] initWithData:ns_data];
    image_data_ = getImageData((NSImage*)ns_image_);
}

MacImage::~MacImage() {
    [(NSImage*)ns_image_ release];
}

}  // namespace mac
}  // namespace asset
}  // namespace temp
